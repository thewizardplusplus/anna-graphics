#include "OpenGlGraphicApi.h"
#include "PlaneMesh.h"
#include "CubeMesh.h"
#include "../../utils/Console.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;
using namespace thewizardplusplus::utils;

const float PLAYER_ROTATE_SPEED = 0.1f;
const float PLAYER_MOVE_SPEED = 0.01f;

int main(void) {
	GraphicApi* graphic_api = GraphicApi::create<OpenGlGraphicApi>();

	World world;

	Camera camera;
	camera.setPosition(0.0f, 0.0f, 1.0f);
	world.setCamera(&camera);

	for (int x = -100; x <= 100; x++) {
		Object* line = new Object();
		line->setPosition(x, 0.0f, 0.0f);

		Mesh* line_mesh = new PlaneMesh(line);
		line_mesh->setScale(0.01f, 100.0f, 1.0f);

		world.addObject(line);
	}

	for (int y = -100; y <= 100; y++) {
		Object* line = new Object();
		line->setPosition(0.0f, y, 0.0f);

		Mesh* line_mesh = new PlaneMesh(line);
		line_mesh->setScale(100.0f, 0.01f, 1.0f);

		world.addObject(line);
	}

	Object* point = new Object();

	Mesh* point_mesh = new CubeMesh(point);
	point_mesh->setScale(0.1f, 0.1f, 0.1f);

	world.addObject(point);

	AnimateObject* gates = AnimateObject::load("data/gates.ao");
	if (gates != NULL) {
		gates->play(true);
		world.addAnimateObject(gates);
	}

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

		world.update(10.0f);

		graphic_api->clear();
		graphic_api->drawWorld(&world);
		window->update();
	}

	delete graphic_api;
	graphic_api = NULL;
}
