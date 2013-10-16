#include "OpenGlGraphicApi.h"
#include "OpenGlWindow.h"
#include "BmpTextureLoader.h"
#include "../../utils/Console.h"
#include "Mesh.h"
#include <GL/gl.h>
#include <cmath>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;
using namespace thewizardplusplus::utils;

const Vector3D<unsigned char> OpenGlGraphicApi::DEFAULT_TEXTURE_LIGHT_COLOR =
	Vector3D<unsigned char>(255, 255, 255);
const Vector3D<unsigned char> OpenGlGraphicApi::DEFAULT_TEXTURE_DARK_COLOR =
	Vector3D<unsigned char>(224, 224, 224);
const std::string             OpenGlGraphicApi::TEXTURE_FROM_DATA_BASE_NAME =
	"texture_from_data_";

OpenGlGraphicApi::OpenGlGraphicApi(void) :
	default_texture(NULL),
	last_id_texture_from_data(0)
{
	window = Window::create<OpenGlWindow>();
	createDefaultTexture();
	addTextureLoader(new BmpTextureLoader());
}

Texture* OpenGlGraphicApi::createTexture(const TextureData& texture_data, const
	std::string& name)
{
	unsigned int opengl_texture = 0;
	glGenTextures(1, &opengl_texture);
	glBindTexture(GL_TEXTURE_2D, opengl_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, 33169 /* GL_GENERATE_MIPMAP */, true);
	glTexImage2D(GL_TEXTURE_2D, 0, !texture_data.isTransparent() ? 3 : 4,
		texture_data.getSize().x, texture_data.getSize().y, 0, !texture_data.
		isTransparent() ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, texture_data.
		getData());

	std::string texture_name = name;
	if (texture_name.empty()) {
		last_id_texture_from_data++;
		std::ostringstream out;
		out << TEXTURE_FROM_DATA_BASE_NAME << last_id_texture_from_data;

		texture_name = out.str();
	}

	Texture* texture = new Texture(texture_name);
	textures[texture] = opengl_texture;

	return texture;
}

void OpenGlGraphicApi::setTexture(Texture* texture) {
	if (texture == NULL) {
		texture = default_texture;
	}

	if (textures.count(texture)) {
		glBindTexture(GL_TEXTURE_2D, textures[texture]);
	}
}

void OpenGlGraphicApi::clear(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGlGraphicApi::processSettingAmbientColor(const Vector3D<float>&
	ambient_color)
{
	float color_array[4] = { ambient_color.x, ambient_color.y, ambient_color.z,
		1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color_array);
}

void OpenGlGraphicApi::processSettingFogParameters(const FogParameters&
	fog_parameters)
{
	switch (fog_parameters.type) {
		case FogType::EXPONENT:
			glFogi(GL_FOG_MODE, GL_EXP);
			break;
		case FogType::SQUARED_EXPONENT:
			glFogi(GL_FOG_MODE, GL_EXP2);
			break;
		case FogType::LINEAR:
		default:
			glFogi(GL_FOG_MODE, GL_LINEAR);
			break;
	}
	float color[4] = { fog_parameters.color.x, fog_parameters.color.y,
		fog_parameters.color.z, 1.0f };
	glFogfv(GL_FOG_COLOR, color);
	glFogf(GL_FOG_DENSITY, fog_parameters.density);
	glFogf(GL_FOG_START, fog_parameters.start_depth);
	glFogf(GL_FOG_END, fog_parameters.end_depth);
}

void OpenGlGraphicApi::setBlendingMode(bool blending_mode) {
	if (blending_mode) {
		glEnable(GL_BLEND);
	} else {
		glDisable(GL_BLEND);
	}
}

void OpenGlGraphicApi::setCamera(Camera* camera) {
	if (camera == NULL) {
		return;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (camera->getType() == CameraType::ORTHOGONAL) {
		glOrtho(0.0, window->getSize().x, window->getSize().y, 0.0, camera->
			getNearPlane(), camera->getFarPlane());
	} else {
		float f = 1.0f / std::tan(camera->getFov() / 2.0f);
		float projection_matrix[] = { f / (static_cast<float>(window->getSize().
			x) / window->getSize().y), 0.0f, 0.0f, 0.0f, 0.0f, f, 0.0f, 0.0f,
			0.0f, 0.0f, (camera->getNearPlane() + camera->getFarPlane()) /
			(camera->getNearPlane() - camera->getFarPlane()), -1.0f, 0.0f, 0.0f,
			(2.0f * camera->getNearPlane() * camera->getFarPlane()) / (camera->
			getNearPlane() - camera->getFarPlane()), 0.0f };
		glMultMatrixf(projection_matrix);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera->getRotation().x, 1.0f, 0.0f, 0.0f);
	glRotatef(camera->getRotation().y, 0.0f, 0.0f, 1.0f);
	glRotatef(camera->getRotation().z, 0.0f, 1.0f, 0.0f);
	glTranslatef(-camera->getPosition().x, -camera->getPosition().z, -camera->
		getPosition().y);
}

void OpenGlGraphicApi::drawMesh(Mesh* mesh) {
	if (mesh == NULL || !mesh->isVisible()) {
		return;
	}

	Object* object = mesh->getObject();
	if (object == NULL || !object->isVisible()) {
		return;
	}

	glTranslatef(object->getPosition().x, object->getPosition().z, -object->
		getPosition().y);
	glRotatef(object->getRotation().x, 1.0f, 0.0f, 0.0f);
	glRotatef(object->getRotation().y, 0.0f, 0.0f, 1.0f);
	glRotatef(object->getRotation().z, 0.0f, 1.0f, 0.0f);
	glScalef(object->getScale().x, object->getScale().z, object->getScale().y);

	glTranslatef(mesh->getPosition().x, mesh->getPosition().z, -mesh->
		getPosition().y);
	glRotatef(mesh->getRotation().x, 1.0f, 0.0f, 0.0f);
	glRotatef(mesh->getRotation().y, 0.0f, 0.0f, 1.0f);
	glRotatef(mesh->getRotation().z, 0.0f, 1.0f, 0.0f);
	glScalef(mesh->getScale().x, mesh->getScale().z, mesh->getScale().y);

	if (ambient_lighting && mesh->getMaterial().allow_ambient_light) {
		glEnable(GL_LIGHTING);
	} else {
		glDisable(GL_LIGHTING);
	}

	if (fog_mode && mesh->getMaterial().allow_fog) {
		glEnable(GL_FOG);
	} else {
		glDisable(GL_FOG);
	}

	setTexture(mesh->getMaterial().texture);
	if (mesh->getMaterial().transparent_type == TransparentType::ALPHA_TEST) {
		glEnable(GL_ALPHA_TEST);
	} else {
		glDisable(GL_ALPHA_TEST);
	}

	for (size_t i = 0; i < mesh->getNumberOfVertices(); i += 3) {
		Vertex* vertex_0 = mesh->getVertex(i);
		Vertex* vertex_1 = mesh->getVertex(i + 1);
		Vertex* vertex_2 = mesh->getVertex(i + 2);
		if (vertex_0 == NULL || vertex_1 == NULL || vertex_2 == NULL) {
			continue;
		}

		glBegin(GL_TRIANGLES);
		glTexCoord2f(vertex_0->uv.x, vertex_0->uv.y);
		glVertex3f(vertex_0->position.x, vertex_0->position.z, -vertex_0->
			position.y);
		glTexCoord2f(vertex_1->uv.x, vertex_1->uv.y);
		glVertex3f(vertex_1->position.x, vertex_1->position.z, -vertex_1->
			position.y);
		glTexCoord2f(vertex_2->uv.x, vertex_2->uv.y);
		glVertex3f(vertex_2->position.x, vertex_2->position.z, -vertex_2->
			position.y);
		glEnd();
	}

	glScalef(1.0f / mesh->getScale().x, 1.0f / mesh->getScale().z, 1.0f / mesh->
		getScale().y);
	glRotatef(-mesh->getRotation().z, 0.0f, 1.0f, 0.0f);
	glRotatef(-mesh->getRotation().y, 0.0f, 0.0f, 1.0f);
	glRotatef(-mesh->getRotation().x, 1.0f, 0.0f, 0.0f);
	glTranslatef(-mesh->getPosition().x, -mesh->getPosition().z, mesh->
		getPosition().y);

	glScalef(1.0f / object->getScale().x, 1.0f / object->getScale().z, 1.0f /
		object->getScale().y);
	glRotatef(-object->getRotation().z, 0.0f, 1.0f, 0.0f);
	glRotatef(-object->getRotation().y, 0.0f, 0.0f, 1.0f);
	glRotatef(-object->getRotation().x, 1.0f, 0.0f, 0.0f);
	glTranslatef(-object->getPosition().x, -object->getPosition().z, object->
		getPosition().y);
}

void OpenGlGraphicApi::createDefaultTexture(void) {
	unsigned char data[DEFAULT_TEXTURE_SIZE * DEFAULT_TEXTURE_SIZE * 3];
	size_t square_size = DEFAULT_TEXTURE_SIZE / DEFAULT_TEXTURE_PIECES;
	bool first_dark = false;
	for (size_t i = 0; i < DEFAULT_TEXTURE_SIZE; i++) {
		if (!(i % square_size)) {
			first_dark = !first_dark;
		}

		bool dark = first_dark;
		for (size_t j = 0; j < DEFAULT_TEXTURE_SIZE; j++) {
			if (!(j % square_size)) {
				dark = !dark;
			}

			size_t index = 3 * (i * DEFAULT_TEXTURE_SIZE + j);
			if (dark) {
				data[index] = DEFAULT_TEXTURE_LIGHT_COLOR.x;
				data[index + 1] = DEFAULT_TEXTURE_LIGHT_COLOR.y;
				data[index + 2] = DEFAULT_TEXTURE_LIGHT_COLOR.z;
			} else {
				data[index] = DEFAULT_TEXTURE_DARK_COLOR.x;
				data[index + 1] = DEFAULT_TEXTURE_DARK_COLOR.y;
				data[index + 2] = DEFAULT_TEXTURE_DARK_COLOR.z;
			}
		}
	}

	default_texture = createTexture(TextureData(&data, Vector2D<size_t>(
		DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE)));
}
