#include "World.h"
#include "DistanceToMeshComparator.h"
#include <algorithm>

using namespace thewizardplusplus::anna::graphics;

World::World(void) :
	camera(NULL)
{}

World::~World(void) {
	ObjectVector::iterator i = objects.begin();
	for (; i != objects.end(); ++i) {
		delete *i;
		*i = NULL;
	}
}

Camera* World::getCamera(void) {
	return camera;
}

void World::setCamera(Camera* camera) {
	this->camera = camera;
}

size_t World::getNumberOfObjects(void) const {
	return objects.size();
}

Object* World::getObject(size_t number) const {
	if (number < objects.size()) {
		return objects[number];
	} else {
		return NULL;
	}
}

void World::addObject(Object* object) {
	if (object == NULL) {
		return;
	}

	for (size_t i = 0; i < object->getNumberOfMeshes(); i++) {
		Mesh* mesh = object->getMesh(i);
		if (mesh->getMaterial().transparent_type == TransparentType::BLENDING) {
			transparent_meshes.push_back(mesh);
		} else {
			opaque_meshes.push_back(mesh);
		}
	}
}

void World::addAnimateObject(AnimateObject* object) {
	addObject(object);
	if (object != NULL) {
		animate_objects.push_back(object);
	}
}

void World::removeObject(Object* object) {
	ObjectVector::iterator index = std::find(objects.begin(), objects.end(),
		object);
	if (index != objects.end()) {
		objects.erase(index);
	}
}

size_t World::getNumberOfOpaqueMeshes(void) const {
	return opaque_meshes.size();
}

Mesh* World::getOpaqueMesh(size_t number) const {
	if (number < opaque_meshes.size()) {
		return opaque_meshes[number];
	} else {
		return NULL;
	}
}

size_t World::getNumberOfTransparentMeshes(void) const {
	return transparent_meshes.size();
}

Mesh* World::getTransparentMesh(size_t number) const {
	if (number < transparent_meshes.size()) {
		return transparent_meshes[number];
	} else {
		return NULL;
	}
}

void World::sortTransparentMeshes(void) {
	if (camera != NULL) {
		std::sort(transparent_meshes.begin(), transparent_meshes.end(),
			DistanceToMeshComparator(camera));
	}
}

void World::update(float delta_time) {
	AnimateObjectVector::const_iterator i = animate_objects.begin();
	for (; i != animate_objects.end(); ++i) {
		(*i)->update(delta_time);
	}
}
