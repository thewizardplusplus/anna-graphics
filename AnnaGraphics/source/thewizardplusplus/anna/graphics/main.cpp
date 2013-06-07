#include "OpenGlGraphicApi.h"
#include "PlaneMesh.h"
#include "CubeMesh.h"
#include "../../utils/Timer.h"
#include "../../utils/Console.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;
using namespace thewizardplusplus::utils;

const int   WORLD_SIZE =          12;
const int   WORLD_STEP =          5;
const float PLAYER_ROTATE_SPEED = 0.1f;
const float PLAYER_MOVE_SPEED =   0.01f;

AnimateObject* animate_object = NULL;

void generateWorld(World* world, GraphicApi* graphic_api) {
	if (world == NULL || graphic_api == NULL) {
		return;
	}

	for (int i = 0; i < WORLD_SIZE; i++) {
		for (int j = 0; j < WORLD_SIZE; j++) {
			Object* object = new Object();
			object->setPosition(Vector3D<float>(static_cast<float>(i *
				WORLD_STEP), static_cast<float>(j * WORLD_STEP), 0.0f));

			Mesh* mesh = new PlaneMesh();
			mesh->setRotation(Vector3D<float>(90.0f, Maths::randomNumber(
				360.0f), 0.0f));
			mesh->getMaterial().texture = graphic_api->createTexture("data/"
				"test_texture.bmp");
			mesh->getMaterial().transparent_type = TransparentType::ALPHA_TEST;
			object->addMesh(mesh);

			world->addObject(object);
		}
	}

	animate_object = new AnimateObject();

	Mesh* mesh = new CubeMesh();
	mesh->getMaterial().texture = graphic_api->createTexture("data/"
		"test_texture.bmp");
	mesh->getMaterial().transparent_type = TransparentType::ALPHA_TEST;
	animate_object->addMesh(mesh);

	world->addAnimateObject(animate_object);

	AnimateTrack* track = new AnimateTrack();
	animate_object->setTrack(track);

	track->addKey(AnimateKey(0, 0, AnimateKeyType::ROTATION, Vector3D<float>(
		0.0f, 0.0f, 0.0f)));
	track->addKey(AnimateKey(0, 25, AnimateKeyType::ROTATION, Vector3D<float>(
		Maths::randomNumber(360.0f), Maths::randomNumber(360.0f), Maths::
		randomNumber(360.0f))));
	track->addKey(AnimateKey(0, 50, AnimateKeyType::ROTATION, Vector3D<float>(
		0.0f, 0.0f, 0.0f)));
	track->addKey(AnimateKey(0, 0, AnimateKeyType::SCALE, Vector3D<float>(1.0f,
		1.0f, 1.0f)));
	track->addKey(AnimateKey(0, 25, AnimateKeyType::SCALE, Vector3D<float>(0.5f,
		0.5f, 0.5f)));
	track->addKey(AnimateKey(0, 50, AnimateKeyType::SCALE, Vector3D<float>(1.0f,
		1.0f, 1.0f)));

	animate_object->play(true);
}

int main(void) {
	Timer timer;

	GraphicApi* graphic_api = GraphicApi::create<OpenGlGraphicApi>();

	World world;
	Camera camera;
	world.setCamera(&camera);
	generateWorld(&world, graphic_api);

	Window* window = graphic_api->getWindow();
	while (!window->isPressedKey(KeyCode::KEY_ESCAPE)) {
		Vector2D<size_t> center = window->getSize() / 2;
		Vector2D<size_t> new_position = window->getPointerPosition();
		window->setPointerPosition(center);
		Vector2D<int> delta = (new_position.convertedTo<int>() - center.
			convertedTo<int>());
		camera.setRotation(camera.getRotation() + Vector3D<float>(
			PLAYER_ROTATE_SPEED * delta.y, 0.0f, PLAYER_ROTATE_SPEED * delta.
			x));
		camera.setRotation(Maths::clamp(camera.getRotation().x, 90.0f, -90.0f),
			camera.getRotation().y, camera.getRotation().z);

		Vector2D<float> direction;
		if (window->isPressedKey(KeyCode::KEY_W)) {
			direction.x += std::cos(Maths::toRadians(camera.getRotation().z -
				90.0f));
			direction.y += std::sin(Maths::toRadians(camera.getRotation().z -
				90.0f));
		} else if (window->isPressedKey(KeyCode::KEY_S)) {
			direction.x += -std::cos(Maths::toRadians(camera.getRotation().z -
				90.0f));
			direction.y += -std::sin(Maths::toRadians(camera.getRotation().z -
				90.0f));
		}
		if (window->isPressedKey(KeyCode::KEY_A)) {
			direction.x += -std::cos(Maths::toRadians(camera.getRotation().z));
			direction.y += -std::sin(Maths::toRadians(camera.getRotation().z));
		} else if (window->isPressedKey(KeyCode::KEY_D)) {
			direction.x += std::cos(Maths::toRadians(camera.getRotation().z));
			direction.y += std::sin(Maths::toRadians(camera.getRotation().z));
		}
		direction.normalize();
		camera.setPosition(camera.getPosition() + Vector3D<float>(
			PLAYER_MOVE_SPEED * direction.x, PLAYER_MOVE_SPEED * direction.y,
			0.0f));

		if (window->isPressedKey(KeyCode::KEY_SPACE)) {
			animate_object->pause(false);
		} else {
			animate_object->pause(true);
		}

		size_t elapsed_time = timer.getElapsedTimeInUs();
		timer.start();

		world.update(elapsed_time / 1000.0f);

		graphic_api->clear();
		graphic_api->drawWorld(&world);
		window->update();

		Console::information() << 1000000.0f / elapsed_time << " fps.";
	}

	delete graphic_api;
	graphic_api = NULL;
}
