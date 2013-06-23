#include "AnimateObject.h"
#include "../../utils/Console.h"
#include "Mesh.h"
#include "../../utils/Path.h"
#include "GraphicApi.h"
#include <fstream>
#include <algorithm>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;
using namespace thewizardplusplus::utils;

AnimateObject* AnimateObject::load(const std::string& filename, GraphicApi*
	graphic_api, bool load_animation)
{
	std::ifstream file;
	file.open(filename.c_str(), std::ios_base::in | std::ios_base::binary);
	if (!file.is_open()) {
		Console::error() << "Warning: unable to open object file \"" << filename
			<< "\".";
		return NULL;
	}

	std::string mesh_path = Path(filename).getPathWithoutFilename();
	AnimateObject* result = new AnimateObject();
	AnimateTrack* track =   new AnimateTrack();
	file.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::
		ifstream::badbit);
	try {
		testMark(file, "object:");
		testMark(file, "meshes:");
		testMark(file, "number:");

		size_t number_of_meshes = 0;
		file >> number_of_meshes;
		for (size_t i = 0; i < number_of_meshes; i++) {
			testMark(file, "mesh:");

			Mesh* mesh = new Mesh(result);
			result->addMesh(mesh);

			testMark(file, "position:");
			Vector3D<float> position;
			file >> position.x >> position.y >> position.z;
			mesh->setPosition(position);

			testMark(file, "rotation:");
			Vector3D<float> rotation;
			file >> rotation.x >> rotation.y >> rotation.z;
			mesh->setRotation(rotation);

			testMark(file, "scale:");
			Vector3D<float> scale;
			file >> scale.x >> scale.y >> scale.z;
			mesh->setScale(scale);

			testMark(file, "material:");
			testMark(file, "texture:");
			std::string texture_path;
			file >> texture_path;
			if (graphic_api != NULL) {
				mesh->getMaterial().texture = graphic_api->createTexture(
					mesh_path + texture_path);
			}
			testMark(file, "transparency_type:");
			std::string transparent_type_name;
			file >> transparent_type_name;
			if (transparent_type_name == "NONE") {
				mesh->getMaterial().transparent_type = TransparentType::NONE;
			} else if (transparent_type_name == "ALPHA_TEST") {
				mesh->getMaterial().transparent_type = TransparentType::
					ALPHA_TEST;
			} else if (transparent_type_name == "BLENDING") {
				mesh->getMaterial().transparent_type = TransparentType::
					BLENDING;
			}
			testMark(file, "allow_ambient_light:");
			file >> std::boolalpha >> mesh->getMaterial().allow_ambient_light;
			testMark(file, "allow_fog:");
			file >> std::boolalpha >> mesh->getMaterial().allow_fog;

			testMark(file, "vertices:");
			testMark(file, "number:");
			size_t number_of_vertices = 0;
			file >> number_of_vertices;
			for (size_t j = 0; j < number_of_vertices; j++) {
				testMark(file, "vertex:");

				Vertex* vertex = new Vertex();
				mesh->addVertex(vertex);

				testMark(file, "position:");
				file >> vertex->position.x >> vertex->position.y >> vertex->
					position.z;

				testMark(file, "uv:");
				file >> vertex->uv.x >> vertex->uv.y;
			}
		}

		if (load_animation) {
			testMark(file, "animation_keys:");
			testMark(file, "number:");
			size_t number_of_keys = 0;
			file >> number_of_keys;
			for (size_t k = 0; k < number_of_keys; k++) {
				testMark(file, "key:");

				AnimateKey key;
				key.valid = true;
				testMark(file, "index_of_mesh:");
				file >> key.index_of_mesh;
				testMark(file, "frame:");
				file >> key.frame;
				testMark(file, "type:");
				std::string key_type_name;
				file >> key_type_name;
				if (key_type_name == "POSITION") {
					key.type = AnimateKeyType::POSITION;
				} else if (key_type_name == "ROTATION") {
					key.type = AnimateKeyType::ROTATION;
				} else if (key_type_name == "SCALE") {
					key.type = AnimateKeyType::SCALE;
				}
				testMark(file, "transformation:");
				file >> key.transformation.x >> key.transformation.y >> key.
					transformation.z;

				track->addKey(key);
			}
			if (number_of_keys > 0) {
				result->setTrack(track);
			} else {
				delete track;
				track = NULL;
			}
		}

		return result;
	} catch (const std::ifstream::failure& exception) {
		delete track;
		track = NULL;

		delete result;
		result = NULL;

		Console::error() << "Warning: invalid format of object file \"" <<
			filename << "\" - " << exception.what() << ".";
		return NULL;
	}
}

AnimateObject::AnimateObject(void) :
	track(NULL),
	fps(25),
	state(AnimateState::STOPPED),
	start_frame(0),
	end_frame(0),
	loop(false),
	current_time(0.0f)
{}

AnimateTrack* AnimateObject::getTrack(void) const {
	return track;
}

void AnimateObject::setTrack(AnimateTrack* track) {
	this->track = track;
}

size_t AnimateObject::getNumberOfFrames(void) const {
	if (track != NULL) {
		return track->getNumberOfFrames();
	} else {
		return 0;
	}
}

size_t AnimateObject::getFps(void) const {
	return fps;
}

void AnimateObject::setFps(size_t fps) {
	this->fps = fps;
}

AnimateState::Types AnimateObject::getState(void) const {
	return state;
}

size_t AnimateObject::getStartFrame(void) const {
	return start_frame;
}

size_t AnimateObject::getEndFrame(void) const {
	return end_frame;
}

bool AnimateObject::isLoop(void) const {
	return loop;
}

size_t AnimateObject::getCurrentFrame(void) const {
	return static_cast<size_t>(Maths::clamp(std::floor(current_time * fps /
		1000.0f), static_cast<float>(getNumberOfFrames())));
}

float AnimateObject::getCurrentTime(void) const {
	return current_time;
}

void AnimateObject::play(bool loop, size_t start_frame, size_t end_frame) {
	if (track == NULL) {
		return;
	}

	this->start_frame = static_cast<size_t>(Maths::clamp(static_cast<float>(
		start_frame), static_cast<float>(getNumberOfFrames())));
	this->end_frame = static_cast<size_t>(Maths::clamp(static_cast<float>(
		end_frame), static_cast<float>(getNumberOfFrames())));
	this->loop = loop;

	stop(start_frame);
	state = AnimateState::PLAYING;
}

void AnimateObject::play(bool loop) {
	play(loop, 0, getNumberOfFrames());
}

void AnimateObject::pause(bool pause) {
	if (pause) {
		state = AnimateState::PAUSED;
	} else if (track != NULL) {
		state = AnimateState::PLAYING;
	}
}

void AnimateObject::stop(size_t frame) {
	state = AnimateState::STOPPED;
	current_time = Maths::clamp(static_cast<float>(frame), 0.0f, static_cast<
		float>(getNumberOfFrames())) / fps * 1000.0f;
	processUpdate();
}

void AnimateObject::stop(void) {
	stop(start_frame);
}

void AnimateObject::update(float delta_time_in_ms) {
	if (track == NULL || state != AnimateState::PLAYING) {
		return;
	}

	current_time += delta_time_in_ms;
	float finish_time = 1000.0f * end_frame / fps;
	if (current_time > finish_time) {
		if (!loop) {
			state = AnimateState::STOPPED;
		} else {
			state = AnimateState::PLAYING;
			current_time -= finish_time;
		}
	}

	processUpdate();
}

void AnimateObject::testMark(std::ifstream& in, const std::string& mark) {
	std::string buffer;
	in >> buffer;

	if (buffer != mark) {
		size_t position = static_cast<size_t>(in.tellg());
		char* buffer = new char[position + 1];
		in.seekg(std::ifstream::beg);
		in.read(buffer, position);

		std::string begin(buffer, position);
		size_t line = std::count(begin.begin(), begin.end(), '\n') + 1;
		size_t column = 0;
		if (line != 1) {
			column = begin.substr(begin.find_last_of('\n') + 1).length() - mark.
				length();
		}

		throw std::ifstream::failure("expected mark \"" + mark + "\" on line " +
			Converter::toString(line) + " and column " + Converter::toString(
			column));
	}
}

void AnimateObject::processUpdate(void) {
	size_t frame = getCurrentFrame();
	float reduced_time = 1000.0f * frame / fps;
	float current_shift = current_time - reduced_time;
	float frame_time = 1000.0f / fps;

	for (size_t i = 0; i < meshes.size(); i++) {
		Mesh* mesh = meshes[i];

		AnimateKey previous_position_key;
		AnimateKey next_position_key;
		AnimateKey previous_rotation_key;
		AnimateKey next_rotation_key;
		AnimateKey previous_scale_key;
		AnimateKey next_scale_key;
		for (size_t j = 0; j < track->getNumberOfKeys(); j++) {
			AnimateKey key = track->getKey(j);
			if (!key.valid || key.index_of_mesh != i) {
				continue;
			}

			if (key.type == AnimateKeyType::POSITION) {
				if (previous_position_key.valid) {
					if (key.frame < previous_position_key.frame) {
						previous_position_key = key;
					}
				} else {
					previous_position_key = key;
				}
				if (next_position_key.valid) {
					if (key.frame > next_position_key.frame) {
						next_position_key = key;
					}
				} else {
					next_position_key = key;
				}
			} else if (key.type == AnimateKeyType::ROTATION) {
				if (previous_rotation_key.valid) {
					if (key.frame < previous_rotation_key.frame) {
						previous_rotation_key = key;
					}
				} else {
					previous_rotation_key = key;
				}
				if (next_rotation_key.valid) {
					if (key.frame > next_rotation_key.frame) {
						next_rotation_key = key;
					}
				} else {
					next_rotation_key = key;
				}
			} else if (key.type == AnimateKeyType::SCALE) {
				if (previous_scale_key.valid) {
					if (key.frame < previous_scale_key.frame) {
						previous_scale_key = key;
					}
				} else {
					previous_scale_key = key;
				}
				if (next_scale_key.valid) {
					if (key.frame > next_scale_key.frame) {
						next_scale_key = key;
					}
				} else {
					next_scale_key = key;
				}
			}
		}

		for (size_t j = 0; j < track->getNumberOfKeys(); j++) {
			AnimateKey key = track->getKey(j);
			if (!key.valid || key.index_of_mesh != i) {
				continue;
			}

			if (key.type == AnimateKeyType::POSITION) {
				if (key.frame <= frame) {
					if (key.frame > previous_position_key.frame) {
						previous_position_key = key;
					}
				} else {
					if (key.frame < next_position_key.frame) {
						next_position_key = key;
					}
				}
			} else if (key.type == AnimateKeyType::ROTATION) {
				if (key.frame <= frame) {
					if (key.frame > previous_rotation_key.frame) {
						previous_rotation_key = key;
					}
				} else {
					if (key.frame < next_rotation_key.frame) {
						next_rotation_key = key;
					}
				}
			} else if (key.type == AnimateKeyType::SCALE) {
				if (key.frame <= frame) {
					if (key.frame > previous_scale_key.frame) {
						previous_scale_key = key;
					}
				} else {
					if (key.frame < next_scale_key.frame) {
						next_scale_key = key;
					}
				}
			}
		}

		Vector3D<float> start;
		Vector3D<float> finish;
		Vector3D<float> current;
		if (previous_position_key.valid && next_position_key.valid) {
			if (previous_position_key.frame != next_position_key.frame) {
				start = previous_position_key.transformation;
				finish = next_position_key.transformation;
				float difference = (next_position_key.frame -
					previous_position_key.frame) * frame_time;
				float shift = (frame - previous_position_key.frame) *
					frame_time;
				float global_shift = shift + current_shift;
				global_shift /= difference;
				current = start.interpolatedTo(finish, global_shift);
			} else {
				current = previous_position_key.transformation;
			}
			mesh->setPosition(current);
		}
		if (previous_rotation_key.valid && next_rotation_key.valid) {
			if (previous_rotation_key.frame != next_rotation_key.frame) {
				start = previous_rotation_key.transformation;
				finish = next_rotation_key.transformation;
				float difference = (next_rotation_key.frame -
					previous_rotation_key.frame) * frame_time;
				float shift = (frame - previous_rotation_key.frame) *
					frame_time;
				float global_shift = shift + current_shift;
				global_shift /= difference;
				current = start.interpolatedTo(finish, global_shift);
			} else {
				current = previous_rotation_key.transformation;
			}
			mesh->setRotation(current);
		}
		if (previous_scale_key.valid && next_scale_key.valid) {
			if (previous_scale_key.frame != next_scale_key.frame) {
				start = previous_scale_key.transformation;
				finish = next_scale_key.transformation;
				float difference = (next_scale_key.frame -
					previous_scale_key.frame) * frame_time;
				float shift = (frame - previous_scale_key.frame) * frame_time;
				float global_shift = shift + current_shift;
				global_shift /= difference;
				current = start.interpolatedTo(finish, global_shift);
			} else {
				current = previous_scale_key.transformation;
			}
			mesh->setScale(current);
		}
	}
}
