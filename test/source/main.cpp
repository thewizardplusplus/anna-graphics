#include <anna/graphics/OpenGlGraphicApi.h>
#include <anna/graphics/CubeMesh.h>
#include <pthread.h>
#include <ctime>
#include <iostream>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

static const float CAMERA_ROTATION_RADIUS = 5;
static const float CAMERA_ROTATION_SPEED = 50;

// http://stackoverflow.com/a/20105913/3884331
int Dummy(void) {
	static int level_of_concurrency = pthread_getconcurrency();
	return level_of_concurrency;
}

std::string GetBasePath(const std::string& app_path) {
	std::string base_path;
	size_t separator_index = app_path.rfind('/');
	if (separator_index != std::string::npos) {
		base_path = app_path.substr(0, separator_index + 1);
	}

	return base_path;
}

float GetCurrentTime(void) {
	return static_cast<float>(std::clock()) / CLOCKS_PER_SEC;
}

int main(int number_of_arguments, char* arguments[]) try {
	(void)number_of_arguments;

	GraphicApi* gapi = GraphicApi::create<OpenGlGraphicApi>();

	World world;

	Camera camera;
	camera.setPosition(0, 0, 2.5);
	camera.setRotation(15, 0, 0);
	world.setCamera(&camera);

	std::string base_path = GetBasePath(arguments[0]);
	AnimateObject* ground = AnimateObject::load(
		base_path
			+ "data/models/ground.ao",
		gapi,
		false
	);
	ground->setScale(10, 10, 10);
	world.addObject(ground);

	AnimateObject* tree = AnimateObject::load(
		base_path
			+ "data/models/tree.ao",
		gapi,
		false
	);
	tree->setPosition(0.0f, 5.0f, 0.0f);
	tree->setScale(0.25f, 0.25f, 0.25f);
	//world.addObject(tree);

	AnimateObject* windmill = AnimateObject::load(
		base_path
			+ "data/models/windmill.ao",
		gapi
	);
	windmill->setPosition(0.0f, 5.0f, 0.0f);
	windmill->setScale(0.25f, 0.25f, 0.25f);
	windmill->play(true);
	//world.addAnimateObject(windmill);

	Window* window = gapi->getWindow();
	float last_time = GetCurrentTime();
	while (!window->isPressedKey(KeyCode::KEY_ESCAPE)) {
		float current_time = GetCurrentTime();
		float x =
			CAMERA_ROTATION_RADIUS
			* std::cos(CAMERA_ROTATION_SPEED * current_time);
		float y =
			CAMERA_ROTATION_RADIUS
			* std::sin(CAMERA_ROTATION_SPEED * current_time);
		camera.setPosition(x, y, camera.getPosition().z);
		camera.setRotation(
			camera.getRotation().x,
			camera.getRotation().y,
			Maths::toDegrees(std::atan2(y, x)) - 90
		);

		world.update(1000 * (current_time - last_time));
		last_time = current_time;

		gapi->clear();
		gapi->drawWorld(&world);
		window->update();
	}

	delete gapi;
} catch (const std::exception& exception) {
	std::cerr << exception.what() << std::endl;
}
