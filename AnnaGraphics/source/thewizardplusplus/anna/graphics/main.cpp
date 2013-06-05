#include "OpenGlGraphicApi.h"
#include "PngTextureLoader.h"
#include "CubeMesh.h"
#include "PlaneMesh.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

const int   WORLD_SIZE =          12;
const int   WORLD_STEP =          5;
const float PLAYER_ROTATE_SPEED = 0.1f;
const float PLAYER_MOVE_SPEED =   0.01f;

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
				"wall0.png");
			object->addMesh(mesh);

			world->addObject(object);
		}
	}
}

void createGui(World* gui, GraphicApi* graphic_api) {
	Object* life_counter_background = new Object();
	life_counter_background->setPosition(Vector3D<float>(105.0f, 10.0f,
		graphic_api->getWindow()->getSize().y - 55.0f));
	life_counter_background->setScale(Vector3D<float>(100.0f, 1.0f, 50.0f));

	PlaneMesh* life_counter_background_mesh = new PlaneMesh();
	life_counter_background_mesh->setRotation(Vector3D<float>(90.0f, 0.0f,

		0.0f));
	life_counter_background->addMesh(life_counter_background_mesh);

	gui->addObject(life_counter_background);

	Object* life_counter = new Object();
	life_counter->setPosition(Vector3D<float>(104.0f, 9.0f, graphic_api->
		getWindow()->getSize().y - 55.0f));
	life_counter->setScale(Vector3D<float>(90.0f, 1.0f, 40.0f));

	PlaneMesh* life_counter_mesh = new PlaneMesh();
	life_counter_mesh->setRotation(Vector3D<float>(90.0f, 0.0f, 0.0f));
	life_counter->addMesh(life_counter_mesh);

	gui->addObject(life_counter);
}

int main(void) {
	GraphicApi* graphic_api = GraphicApi::create<OpenGlGraphicApi>();
	graphic_api->addTextureLoader(new PngTextureLoader());

	World world;
	Camera camera;
	world.setCamera(&camera);
	generateWorld(&world, graphic_api);

	World gui;
	Camera gui_camera(CameraType::ORTHOGONAL);
	gui.setCamera(&gui_camera);
	createGui(&gui, graphic_api);

	Window* window = graphic_api->getWindow();
	while (!window->isPressedKey(KeyCode::KEY_ESCAPE)) {
		Vector2D<size_t> center = window->getSize() / 2;
		Vector2D<size_t> new_position = window->getPointerPosition();
		window->setPointerPosition(center);
		Vector2D<int> delta = new_position.convertedTo<int>() - center.
			convertedTo<int>();
		camera.rotation += Vector3D<float>(0.0f, 0.0f, PLAYER_ROTATE_SPEED *
			delta.x);
		camera.rotation += Vector3D<float>(PLAYER_ROTATE_SPEED * delta.y, 0.0f,
			0.0f);
		camera.rotation.x = Maths::clamp(camera.rotation.x, 90.0f, -90.0f);

		Vector2D<float> direction;
		if (window->isPressedKey(KeyCode::KEY_W)) {
			direction.x += std::cos(Maths::toRadians(camera.rotation.z -
				90.0f));
			direction.y += std::sin(Maths::toRadians(camera.rotation.z -
				90.0f));
		} else if (window->isPressedKey(KeyCode::KEY_S)) {
			direction.x += -std::cos(Maths::toRadians(camera.rotation.z -
				90.0f));
			direction.y += -std::sin(Maths::toRadians(camera.rotation.z -
				90.0f));
		}
		if (window->isPressedKey(KeyCode::KEY_A)) {
			direction.x += -std::cos(Maths::toRadians(camera.rotation.z));
			direction.y += -std::sin(Maths::toRadians(camera.rotation.z));
		} else if (window->isPressedKey(KeyCode::KEY_D)) {
			direction.x += std::cos(Maths::toRadians(camera.rotation.z));
			direction.y += std::sin(Maths::toRadians(camera.rotation.z));
		}
		direction.normalize();
		camera.position += Vector3D<float>(PLAYER_MOVE_SPEED * direction.x,
			PLAYER_MOVE_SPEED * direction.y, 0.0f);

		graphic_api->clear();
		graphic_api->drawWorld(&world);
		graphic_api->drawWorld(&gui);
		window->update();
	}

	delete graphic_api;
	graphic_api = NULL;
}
