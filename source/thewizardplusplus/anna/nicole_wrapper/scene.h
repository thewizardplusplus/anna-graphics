#ifndef SCENE_H
#define SCENE_H

#include "../graphics/World.h"
#include <list>

namespace thewizardplusplus {
namespace anna {
namespace nicole_framework {

typedef std::list<anna::graphics::World*> WorldList;

extern "C" {

float SceneCreate(void);
float SceneGetCameraType(float scene_id);
void SceneSetCameraType(float camera_type, float scene_id);
float SceneGetCameraPositionX(float scene_id);
float SceneGetCameraPositionY(float scene_id);
float SceneGetCameraPositionZ(float scene_id);
void SceneSetCameraPosition(float z, float y, float x, float scene_id);
float SceneGetCameraRotationX(float scene_id);
float SceneGetCameraRotationY(float scene_id);
float SceneGetCameraRotationZ(float scene_id);
void SceneSetCameraRotation(float z, float y, float x, float scene_id);
void SceneUpdate(float delta_time_in_ms, float scene_id);
void SceneDelete(float scene_id);
anna::graphics::World* SceneGetById(float scene_id);

}

}
}
}
#endif
