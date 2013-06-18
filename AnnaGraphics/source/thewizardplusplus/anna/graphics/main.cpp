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

int main(void) {
	Timer timer;

	GraphicApi* graphic_api = GraphicApi::create<OpenGlGraphicApi>();
	Window* window = graphic_api->getWindow();

	World world;
	Camera camera;
	camera.setType(CameraType::ORTHOGONAL);
	world.setCamera(&camera);
	AnimateObject* object = AnimateObject::loadFromFile("data/gates.ao");
	object->setScale(1000, 1000, 1000);
	object->play(true);
	world.addAnimateObject(object);

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

		size_t elapsed_time = timer.getElapsedTimeInUs();
		timer.start();

		world.update(elapsed_time / 1000.0f);

		graphic_api->clear();
		graphic_api->drawWorld(&world);
		window->update();

		//Console::information() << 1000000.0f / elapsed_time << " fps.";
	}

	delete graphic_api;
	graphic_api = NULL;
}
