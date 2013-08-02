#include "entity.h"
#include "graphic_core.h"
#include "scene.h"
#include "utils.h"
#include <iostream>

using namespace thewizardplusplus::anna::nicole_framework;
using namespace thewizardplusplus::anna::graphics;

static AnimateObjectList objects;

extern "C" float EntityLoadFromFile(const char* filename, float scene_id) {
	if (graphic_api == NULL) {
		Error("Graphics core can be opened only once.");
	}

	AnimateObject* object = AnimateObject::load(filename, graphic_api);
	if (object == NULL) {
		Error(std::string("Unable to load object from file \"") + filename +
			"\".");
	}

	World* world = SceneGetById(scene_id);
	world->addAnimateObject(object);
	objects.push_back(object);

	return objects.size() - 1;
}

extern "C" float EntityGetPositionX(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getPosition().x;
}

extern "C" float EntityGetPositionY(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getPosition().y;
}

extern "C" float EntityGetPositionZ(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getPosition().z;
}

extern "C" void EntitySetPosition(float z, float y, float x, float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	object->setPosition(x, y, z);
}

extern "C" float EntityGetRotationX(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getRotation().x;
}

extern "C" float EntityGetRotationY(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getRotation().y;
}

extern "C" float EntityGetRotationZ(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getRotation().z;
}

extern "C" void EntitySetRotation(float z, float y, float x, float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	object->setRotation(x, y, z);
}

extern "C" float EntityGetScaleX(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getScale().x;
}

extern "C" float EntityGetScaleY(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getScale().y;
}

extern "C" float EntityGetScaleZ(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getScale().z;
}

extern "C" void EntitySetScale(float z, float y, float x, float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	object->setScale(x, y, z);
}

extern "C" float EntityIsVisible(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->isVisible();
}

extern "C" void EntitySetVisible(float entity_visible, float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	object->setVisible(entity_visible);
}

extern "C" float EntityGetNumberOfFrames(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getNumberOfFrames();
}

extern "C" float EntityGetFps(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getFps();
}

extern "C" void EntitySetFps(float entity_fps, float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	object->setFps(entity_fps);
}

extern "C" float EntityGetState(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getState();
}

extern "C" float EntityGetStartFrame(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getStartFrame();
}

extern "C" float EntityGetEndFrame(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getEndFrame();
}

extern "C" float EntityIsLoop(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->isLoop();
}

extern "C" float EntityGetCurrentFrame(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getCurrentFrame();
}

extern "C" float EntityGetCurrentTime(float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	return object->getCurrentTime();
}

extern "C" void EntityPlay(float end_frame, float start_frame, float loop, float
	entity_id)
{
	AnimateObject* object = EntityGetById(entity_id);
	object->play(loop, start_frame, end_frame);
}

extern "C" void EntityPause(bool pause, float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	object->pause(pause);
}

extern "C" void EntityStop(float frame, float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	object->stop(frame);
}

extern "C" void EntityUpdate(float delta_time_in_ms, float entity_id) {
	AnimateObject* object = EntityGetById(entity_id);
	object->update(delta_time_in_ms);
}

extern "C" void EntityDelete(float entity_id) {
	if (entity_id >= 0 && entity_id < objects.size()) {
		AnimateObjectList::iterator index = objects.begin();
		std::advance(index, entity_id);

		if (*index != NULL) {
			delete *index;
			*index = NULL;
		}

		return;
	}

	Error("Invalid object ID " + ConvertToString(entity_id) + ".");
}

extern "C" AnimateObject* EntityGetById(float entity_id) {
	if (entity_id >= 0 && entity_id < objects.size()) {
		AnimateObjectList::const_iterator index = objects.begin();
		std::advance(index, entity_id);

		AnimateObject* object = *index;
		if (object != NULL) {
			return object;
		}
	}

	Error("Invalid object ID " + ConvertToString(entity_id) + ".");
	return NULL;
}
