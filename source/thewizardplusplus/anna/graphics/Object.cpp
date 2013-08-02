#include "Object.h"
#include "Mesh.h"
#include <algorithm>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

Object::Object(void) :
	scale(1.0f, 1.0f, 1.0f),
	visible(true)
{}

Object::~Object(void) {
	MeshVector::iterator i = meshes.begin();
	for (; i != meshes.end(); ++i) {
		delete *i;
		*i = NULL;
	}
}

size_t Object::getNumberOfMeshes(void) const {
	return meshes.size();
}

Mesh* Object::getMesh(size_t number) const {
	if (number < meshes.size()) {
		return meshes[number];
	} else {
		return NULL;
	}
}

void Object::addMesh(Mesh* mesh) {
	if (mesh != NULL && mesh->getObject() != this) {
		meshes.push_back(mesh);
		mesh->setObject(this);
	}
}

void Object::removeMesh(Mesh* mesh) {
	if (mesh != NULL) {
		MeshVector::iterator index = std::find(meshes.begin(), meshes.end(),
			mesh);
		if (index != meshes.end()) {
			meshes.erase(index);
		}

		mesh->setObject(NULL);
	}
}

Vector3D<float> Object::getPosition(void) const {
	return position;
}

void Object::setPosition(const Vector3D<float>& position) {
	this->position = position;
}

void Object::setPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

Vector3D<float> Object::getRotation(void) const {
	return rotation;
}

void Object::setRotation(const Vector3D<float>& rotation) {
	this->rotation = rotation;
}

void Object::setRotation(float x, float y, float z) {
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

Vector3D<float> Object::getScale(void) const {
	return scale;
}

void Object::setScale(const Vector3D<float>& scale) {
	this->scale = scale;
}

void Object::setScale(float x, float y, float z) {
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

bool Object::isVisible(void) const {
	return visible;
}

void Object::setVisible(bool visible) {
	this->visible = visible;
}
