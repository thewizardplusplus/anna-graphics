#include <anna/graphics/OpenGlGraphicApi.h>
#include <anna/graphics/CubeMesh.h>
#include <pthread.h>
#include <iostream>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

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

int main(int number_of_arguments, char* arguments[]) try {
	(void)number_of_arguments;

	GraphicApi* gapi = GraphicApi::create<OpenGlGraphicApi>();

	World world;

	Camera camera;
	world.setCamera(&camera);

	std::string base_path = GetBasePath(arguments[0]);
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
	while (!window->isPressedKey(KeyCode::KEY_ESCAPE)) {
		windmill->setRotation(
			windmill->getRotation()
			+ Vector3D<float>(0.0f, 0.0f, 1.0f)
		);
		world.update(1000.0f / 60.0f);

		gapi->clear();
		gapi->drawWorld(&world);
		window->update();
	}

	delete gapi;
	gapi = NULL;
} catch (const std::exception& exception) {
	std::cerr << exception.what() << std::endl;
}
