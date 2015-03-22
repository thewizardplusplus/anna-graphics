#include <anna/graphics/OpenGlGraphicApi.h>
#include <anna/graphics/FogParameters.h>
#include <anna/graphics/Skybox.h>
#include <pthread.h>
#include <ctime>
#include <iostream>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

static const std::string DATA_PATH = "data/";
static const std::string TEXTURES_PATH = DATA_PATH + "textures/";
static const std::string MODELS_PATH = DATA_PATH + "models/";
static const float DEFAULT_CAMERA_ANGLE = 6.23;
static const size_t NUMBER_OF_TREES = 75;
static const float CAMERA_ROTATION_RADIUS = 5;
static const float CAMERA_ROTATION_SPEED = 0.5;
static const float ANIMATION_SPEED = 25;

Camera* MakeCamera(World* world);
void SetFog(GraphicApi* gapi);
std::string GetBasePath(const std::string& app_path);
void MakeSkybox(World* world, GraphicApi* gapi, const std::string& base_path);
void MakeGround(World* world, GraphicApi* gapi, const std::string& base_path);
float GetRandomNumber(float minimum, float maximum);
void MakeForest(World* world, GraphicApi* gapi, const std::string& base_path);
void MakeWindmill(World* world, GraphicApi* gapi, const std::string& base_path);
float GetCurrentTime(void);
void RotateCamera(Camera* camera, float current_time);
void UpdateWorld(World* world, float elapsed_time);
void DrawWorld(World* world, GraphicApi* gapi, Window* window);

int main(int number_of_arguments, char* arguments[]) try {
	(void)number_of_arguments;

	World* world = new World();
	Camera* camera = MakeCamera(world);

	GraphicApi* gapi = GraphicApi::create<OpenGlGraphicApi>();
	SetFog(gapi);

	std::string base_path = GetBasePath(arguments[0]);
	MakeSkybox(world, gapi, base_path);
	MakeGround(world, gapi, base_path);
	MakeForest(world, gapi, base_path);
	MakeWindmill(world, gapi, base_path);

	Window* window = gapi->getWindow();
	float last_time = GetCurrentTime();
	float camera_angle = DEFAULT_CAMERA_ANGLE;
	while (!window->isPressedKey(KeyCode::KEY_ESCAPE)) {
		float current_time = GetCurrentTime();
		float elapsed_time = current_time - last_time;
		last_time = current_time;

		if (window->isPressedKey(KeyCode::KEY_LEFT)) {
			camera_angle += elapsed_time;
		} else if (window->isPressedKey(KeyCode::KEY_RIGHT)) {
			camera_angle += -elapsed_time;
		}
		RotateCamera(camera, camera_angle);

		UpdateWorld(world, elapsed_time);
		DrawWorld(world, gapi, window);
	}

	delete gapi;
	delete camera;
	delete world;
} catch (const std::exception& exception) {
	std::cerr << exception.what() << std::endl;
}

Camera* MakeCamera(World* world) {
	Camera* camera = new Camera();
	camera->setPosition(0, 0, 2);
	camera->setRotation(15, 0, 0);

	world->setCamera(camera);

	return camera;
}

void SetFog(GraphicApi* gapi) {
	FogParameters fog_parameters(Vector3D<float>(0, 0, 0), 1, 1, 7.5);
	gapi->setFogParameters(fog_parameters);

	gapi->setFogMode(true);
}

std::string GetBasePath(const std::string& app_path) {
	std::string base_path;
	size_t separator_index = app_path.rfind('/');
	if (separator_index != std::string::npos) {
		base_path = app_path.substr(0, separator_index + 1);
	}

	return base_path;
}

void MakeSkybox(World* world, GraphicApi* gapi, const std::string& base_path) {
	Object* skybox = new Skybox(
		gapi->createTexture(
			base_path
			+ TEXTURES_PATH
			+ "skybox_axis_z_positive_direction.bmp"
		),
		gapi->createTexture(
			base_path
			+ TEXTURES_PATH
			+ "skybox_axis_z_negative_direction.bmp"
		),
		gapi->createTexture(
			base_path
			+ TEXTURES_PATH
			+ "skybox_axis_x_positive_direction.bmp"
		),
		gapi->createTexture(
			base_path
			+ TEXTURES_PATH
			+ "skybox_axis_y_positive_direction.bmp"
		),
		gapi->createTexture(
			base_path
			+ TEXTURES_PATH
			+ "skybox_axis_x_negative_direction.bmp"
		),
		gapi->createTexture(
			base_path
			+ TEXTURES_PATH
			+ "skybox_axis_y_negative_direction.bmp"
		)
	);
	skybox->setScale(1000, 1000, 1000);

	world->addObject(skybox);
}

void MakeGround(World* world, GraphicApi* gapi, const std::string& base_path) {
	AnimateObject* ground = AnimateObject::load(
		base_path
			+ MODELS_PATH
			+ "ground.ao",
		gapi,
		false
	);
	ground->setScale(10, 10, 10);

	world->addObject(ground);
}

void MakeForest(World* world, GraphicApi* gapi, const std::string& base_path) {
	for (size_t i = 0; i < NUMBER_OF_TREES; i++) {
		AnimateObject* tree = AnimateObject::load(
			base_path
				+ MODELS_PATH
				+ "tree.ao",
			gapi,
			false
		);
		tree->setScale(0.1, 0.1, 0.1);

		float angle = GetRandomNumber(0, 360);
		float radius = GetRandomNumber(1.25, 7.5);
		float x = radius * std::cos(Maths::toRadians(angle));
		float y = radius * std::sin(Maths::toRadians(angle));
		tree->setPosition(x, y, -0.25);

		world->addObject(tree);
	}
}

float GetRandomNumber(float minimum, float maximum) {
	static bool prng_initialized = false;
	if (!prng_initialized) {
		std::srand(std::clock());
		prng_initialized = true;
	}

	return
		static_cast<float>(std::rand()) / RAND_MAX
		* (maximum - minimum)
		+ minimum;
}

void MakeWindmill(
	World* world,
	GraphicApi* gapi,
	const std::string& base_path
) {
	AnimateObject* windmill = AnimateObject::load(
		base_path
			+ MODELS_PATH
			+ "windmill.ao",
		gapi
	);
	windmill->setPosition(0, 0, -0.2);
	windmill->setRotation(0, 0, -120);
	windmill->setScale(0.25, 0.25, 0.25);
	windmill->play(true);

	world->addAnimateObject(windmill);
}

float GetCurrentTime(void) {
	return static_cast<float>(std::clock()) / CLOCKS_PER_SEC;
}

void RotateCamera(Camera* camera, float angle) {
	float x =
		CAMERA_ROTATION_RADIUS
		* std::cos(CAMERA_ROTATION_SPEED * angle);
	float y =
		CAMERA_ROTATION_RADIUS
		* std::sin(CAMERA_ROTATION_SPEED * angle);
	camera->setPosition(x, y, camera->getPosition().z);
	camera->setRotation(
		camera->getRotation().x,
		camera->getRotation().y,
		Maths::toDegrees(std::atan2(y, x)) - 90
	);
}

void UpdateWorld(World* world, float elapsed_time) {
	world->update(1000 * ANIMATION_SPEED * elapsed_time);
}

void DrawWorld(World* world, GraphicApi* gapi, Window* window) {
	gapi->clear();
	gapi->drawWorld(world);
	window->update();
}

// http://stackoverflow.com/a/20105913/3884331
int Dummy(void) {
	static int level_of_concurrency = pthread_getconcurrency();
	return level_of_concurrency;
}
