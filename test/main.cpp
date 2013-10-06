#include <OpenGlGraphicApi.h>
#include <CubeMesh.h>
#include <memory>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

int main(void) {
	std::auto_ptr<GraphicApi> gapi(GraphicApi::create<OpenGlGraphicApi>());

	World world;
	Camera camera;
	world.setCamera(&camera);

	Object* cube = new Object();
	cube->addMesh(new CubeMesh());
	cube->setPosition(0.0f, 5.0f, 0.0f);
	world.addObject(cube);

	Window* wnd = gapi->getWindow();
	while (!wnd->isPressedKey(KeyCode::KEY_ESCAPE)) {
		cube->setRotation(cube->getRotation() + Vector3D<float>(Maths::
			randomNumber(), Maths::randomNumber(), Maths::randomNumber()));

		gapi->clear();
		gapi->drawWorld(&world);
		wnd->update();
	}
}
