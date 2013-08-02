#include "scene.h"
#include "utils.h"

using namespace thewizardplusplus::anna::nicole_framework;
using namespace thewizardplusplus::anna::graphics;

static WorldList worlds;

extern "C" float SceneCreate(void) {
	World* world = new World();
	worlds.push_back(world);

	Camera* camera = new Camera();
	world->setCamera(camera);

	return worlds.size() - 1;
}

extern "C" float SceneGetCameraType(float scene_id) {
	World* world = SceneGetById(scene_id);
	return world->getCamera()->getType();
}

extern "C" void SceneSetCameraType(float camera_type, float scene_id) {
	World* world = SceneGetById(scene_id);
	world->getCamera()->setType(static_cast<CameraType::Types>(camera_type));
}

extern "C" float SceneGetCameraPositionX(float scene_id) {
	World* world = SceneGetById(scene_id);
	return world->getCamera()->getPosition().x;
}

extern "C" float SceneGetCameraPositionY(float scene_id) {
	World* world = SceneGetById(scene_id);
	return world->getCamera()->getPosition().y;
}

extern "C" float SceneGetCameraPositionZ(float scene_id) {
	World* world = SceneGetById(scene_id);
	return world->getCamera()->getPosition().z;
}

extern "C" void SceneSetCameraPosition(float z, float y, float x, float
	scene_id)
{
	World* world = SceneGetById(scene_id);
	world->getCamera()->setPosition(x, y, z);
}

extern "C" float SceneGetCameraRotationX(float scene_id) {
	World* world = SceneGetById(scene_id);
	return world->getCamera()->getRotation().x;
}

extern "C" float SceneGetCameraRotationY(float scene_id) {
	World* world = SceneGetById(scene_id);
	return world->getCamera()->getRotation().y;
}

extern "C" float SceneGetCameraRotationZ(float scene_id) {
	World* world = SceneGetById(scene_id);
	return world->getCamera()->getRotation().z;
}

extern "C" void SceneSetCameraRotation(float z, float y, float x, float
	scene_id)
{
	World* world = SceneGetById(scene_id);
	world->getCamera()->setRotation(x, y, z);
}

extern "C" void SceneUpdate(float delta_time_in_ms, float scene_id) {
	World* world = SceneGetById(scene_id);
	world->update(delta_time_in_ms);
}

extern "C" void SceneDelete(float scene_id) {
	if (scene_id >= 0 && scene_id < worlds.size()) {
		WorldList::iterator index = worlds.begin();
		std::advance(index, scene_id);

		if (*index != NULL) {
			delete (*index)->getCamera();
			(*index)->setCamera(NULL);

			delete *index;
			*index = NULL;
		}

		return;
	}

	Error("Invalid scene ID " + ConvertToString(scene_id) + ".");
}

extern "C" World* SceneGetById(float scene_id) {
	if (scene_id >= 0 && scene_id < worlds.size()) {
		WorldList::const_iterator index = worlds.begin();
		std::advance(index, scene_id);

		World* world = *index;
		if (world != NULL) {
			return world;
		}
	}

	Error("Invalid scene ID " + ConvertToString(scene_id) + ".");
	return NULL;
}
