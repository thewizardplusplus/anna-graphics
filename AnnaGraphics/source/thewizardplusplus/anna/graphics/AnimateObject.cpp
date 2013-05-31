#include "AnimateObject.h"
#include "Mesh.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

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
	return Maths::clamp(std::floor(current_time * fps / 1000.0f),
		getNumberOfFrames());
}

float AnimateObject::getCurrentTime(void) const {
	return current_time;
}

void AnimateObject::play(bool loop, size_t start_frame, size_t end_frame) {
	if (track == NULL) {
		return;
	}

	this->start_frame = Maths::clamp(start_frame, getNumberOfFrames());
	this->end_frame = Maths::clamp(end_frame, getNumberOfFrames());
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
	current_time = Maths::clamp(frame, 0.0f, getNumberOfFrames()) / fps *
		1000.0f;
	processUpdate();
}

void AnimateObject::stop(void) {
	stop(start_frame);
}

void AnimateObject::update(float delta_time) {
	if (track == NULL || state != AnimateState::PLAYING) {
		return;
	}

	current_time += delta_time;
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
