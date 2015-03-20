#include <anna/graphics/OpenGlGraphicApi.h>
#include <anna/graphics/Skybox.h>
#include <anna/graphics/CubeMesh.h>
#include <pthread.h>
#include <ctime>
#include <iostream>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

static const float CAMERA_ROTATION_RADIUS = 5;
static const float CAMERA_ROTATION_SPEED = 2.5;
static const float ANIMATION_SPEED = 25;
static const size_t NUMBER_OF_TREES = 75;

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

float GetRandomNumber(float minimum, float maximum) {
	return
		static_cast<float>(std::rand()) / RAND_MAX * (maximum - minimum)
		+ minimum;
}

float GetCurrentTime(void) {
	return static_cast<float>(std::clock()) / CLOCKS_PER_SEC;
}

int main(int number_of_arguments, char* arguments[]) try {
	(void)number_of_arguments;

	World world;
	Camera camera;
	camera.setPosition(0, 0, 2);
	camera.setRotation(15, 0, 0);
	world.setCamera(&camera);

	std::string base_path = GetBasePath(arguments[0]);
	GraphicApi* gapi = GraphicApi::create<OpenGlGraphicApi>();
	Object* skybox = new Skybox(
		gapi->createTexture(
			base_path
			+ "data/textures/skybox_axis_z_positive_direction.bmp"
		),
		gapi->createTexture(
			base_path
			+ "data/textures/skybox_axis_z_negative_direction.bmp"
		),
		gapi->createTexture(
			base_path
			+ "data/textures/skybox_axis_x_positive_direction.bmp"
		),
		gapi->createTexture(
			base_path
			+ "data/textures/skybox_axis_y_positive_direction.bmp"
		),
		gapi->createTexture(
			base_path
			+ "data/textures/skybox_axis_x_negative_direction.bmp"
		),
		gapi->createTexture(
			base_path
			+ "data/textures/skybox_axis_y_negative_direction.bmp"
		)
	);
	skybox->setScale(1000, 1000, 1000);
	world.addObject(skybox);

	AnimateObject* ground = AnimateObject::load(
		base_path
			+ "data/models/ground.ao",
		gapi,
		false
	);
	ground->setScale(10, 10, 10);
	world.addObject(ground);

	AnimateObject* windmill = AnimateObject::load(
		base_path
			+ "data/models/windmill.ao",
		gapi
	);
	windmill->setPosition(0, 0, -0.2);
	windmill->setRotation(0, 0, -120);
	windmill->setScale(0.25, 0.25, 0.25);
	windmill->play(true);
	world.addAnimateObject(windmill);

	for (size_t i = 0; i < NUMBER_OF_TREES; i++) {
		AnimateObject* tree = AnimateObject::load(
			base_path
				+ "data/models/tree.ao",
			gapi,
			false
		);
		tree->setScale(0.1, 0.1, 0.1);
		world.addObject(tree);

		float angle = GetRandomNumber(0, 360);
		float radius = GetRandomNumber(1.25, 7.5);
		float x = radius * std::cos(Maths::toRadians(angle));
		float y = radius * std::sin(Maths::toRadians(angle));
		tree->setPosition(x, y, -0.25);
	}

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

		world.update(1000 * ANIMATION_SPEED * (current_time - last_time));
		last_time = current_time;

		gapi->clear();
		gapi->drawWorld(&world);
		window->update();
	}

	delete gapi;
} catch (const std::exception& exception) {
	std::cerr << exception.what() << std::endl;
}
