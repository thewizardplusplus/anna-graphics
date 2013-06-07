#ifndef WORLD_H
#define WORLD_H

#include "Camera.h"
#include "Object.h"
#include "AnimateObject.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class World {
public:
	World(void);
	~World(void);
	Camera* getCamera(void);
	void setCamera(Camera* camera);
	size_t getNumberOfObjects(void) const;
	Object* getObject(size_t number) const;
	void addObject(Object* object);
	void addAnimateObject(AnimateObject* object);
	void removeObject(Object* object);
	size_t getNumberOfOpaqueMeshes(void) const;
	Mesh* getOpaqueMesh(size_t number) const;
	size_t getNumberOfTransparentMeshes(void) const;
	Mesh* getTransparentMesh(size_t number) const;
	void sortTransparentMeshes(void);
	void update(float delta_time_in_ms);

private:
	typedef std::vector<Object*>        ObjectVector;
	typedef std::vector<AnimateObject*> AnimateObjectVector;
	typedef std::vector<Mesh*>          MeshVector;

	Camera*             camera;
	ObjectVector        objects;
	AnimateObjectVector animate_objects;
	MeshVector          opaque_meshes;
	MeshVector          transparent_meshes;
};

}
}
}
#endif
