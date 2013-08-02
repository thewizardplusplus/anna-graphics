#ifndef ENTITY_H
#define ENTITY_H

#include "../graphics/AnimateObject.h"
#include <list>

namespace thewizardplusplus {
namespace anna {
namespace nicole_framework {

typedef std::list<anna::graphics::AnimateObject*> AnimateObjectList;

extern "C" {

float EntityLoadFromFile(const char* filename, float scene_id);
float EntityGetPositionX(float entity_id);
float EntityGetPositionY(float entity_id);
float EntityGetPositionZ(float entity_id);
void EntitySetPosition(float z, float y, float x, float entity_id);
float EntityGetRotationX(float entity_id);
float EntityGetRotationY(float entity_id);
float EntityGetRotationZ(float entity_id);
void EntitySetRotation(float z, float y, float x, float entity_id);
float EntityGetScaleX(float entity_id);
float EntityGetScaleY(float entity_id);
float EntityGetScaleZ(float entity_id);
void EntitySetScale(float z, float y, float x, float entity_id);
float EntityIsVisible(float entity_id);
void EntitySetVisible(float entity_visible, float entity_id);
float EntityGetNumberOfFrames(float entity_id);
float EntityGetFps(float entity_id);
void EntitySetFps(float entity_fps, float entity_id);
float EntityGetState(float entity_id);
float EntityGetStartFrame(float entity_id);
float EntityGetEndFrame(float entity_id);
float EntityIsLoop(float entity_id);
float EntityGetCurrentFrame(float entity_id);
float EntityGetCurrentTime(float entity_id);
void EntityPlay(float end_frame, float start_frame, float loop, float
	entity_id);
void EntityPause(bool pause, float entity_id);
void EntityStop(float frame, float entity_id);
void EntityUpdate(float delta_time_in_ms, float entity_id);
void EntityDelete(float entity_id);
anna::graphics::AnimateObject* EntityGetById(float entity_id);

}

}
}
}
#endif
