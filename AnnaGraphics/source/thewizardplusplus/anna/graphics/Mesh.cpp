#include "Mesh.h"
#include "Object.h"
#include <algorithm>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

Mesh::Mesh(Object* object) :
	object(NULL),
	scale(1.0f, 1.0f, 1.0f),
	visible(true)
{
	if (object != NULL) {
		object->addMesh(this);
	}
}

Mesh::~Mesh(void) {
	VertexVector::iterator i = vertices.begin();
	for (; i != vertices.end(); ++i) {
		delete *i;
		*i = NULL;
	}

	if (object != NULL) {
		object->removeMesh(this);
	}
}

Object* Mesh::getObject(void) const {
	return object;
}

void Mesh::setObject(Object* object) {
	if (object != NULL && this->object != object) {
		this->object = object;
		object->addMesh(this);
	}
}

size_t Mesh::getNumberOfVertices(void) const {
	return vertices.size();
}

Vertex* Mesh::getVertex(size_t number) const {
	if (number < vertices.size()) {
		return vertices[number];
	} else {
		return NULL;
	}
}

void Mesh::addVertex(Vertex* vertex) {
	if (vertex != NULL) {
		vertices.push_back(vertex);
	}
}

void Mesh::removeVertex(Vertex* vertex) {
	VertexVector::iterator index = std::find(vertices.begin(), vertices.end(),
		vertex);
	if (index != vertices.end()) {
		vertices.erase(index);
	}
}

size_t Mesh::getNumberOfTriangles(void) const {
	return vertices.size() / 3;
}

Vector3D<float> Mesh::getPosition(void) const {
	return position;
}

void Mesh::setPosition(const Vector3D<float>& position) {
	this->position = position;
}

void Mesh::setPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

Vector3D<float> Mesh::getRotation(void) const {
	return rotation;
}

void Mesh::setRotation(const Vector3D<float>& rotation) {
	this->rotation = rotation;
}

void Mesh::setRotation(float x, float y, float z) {
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

Vector3D<float> Mesh::getScale(void) const {
	return scale;
}

void Mesh::setScale(const Vector3D<float>& scale) {
	this->scale = scale;
}

void Mesh::setScale(float x, float y, float z) {
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

Material& Mesh::getMaterial(void) {
	return material;
}

bool Mesh::isVisible(void) const {
	return visible;
}

void Mesh::setVisible(bool visible) {
	this->visible = visible;
}
