#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "Material.h"
#include <vector>

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class Object;

class Mesh {
public:
	explicit Mesh(Object* object = NULL);
	virtual ~Mesh(void);
	Object* getObject(void) const;
	void setObject(Object* object);
	size_t getNumberOfVertices(void) const;
	Vertex* getVertex(size_t number) const;
	void addVertex(Vertex* vertex);
	void removeVertex(Vertex* vertex);
	size_t getNumberOfTriangles(void) const;
	maths::Vector3D<float> getPosition(void) const;
	void setPosition(const maths::Vector3D<float>& position);
	void setPosition(float x, float y, float z);
	maths::Vector3D<float> getRotation(void) const;
	void setRotation(const maths::Vector3D<float>& rotation);
	void setRotation(float x, float y, float z);
	maths::Vector3D<float> getScale(void) const;
	void setScale(const maths::Vector3D<float>& scale);
	void setScale(float x, float y, float z);
	Material& getMaterial(void);
	bool isVisible(void) const;
	void setVisible(bool visible);

protected:
	typedef std::vector<Vertex*> VertexVector;

	Object*                object;
	VertexVector           vertices;
	maths::Vector3D<float> position;
	maths::Vector3D<float> rotation;
	maths::Vector3D<float> scale;
	Material               material;
	bool                   visible;
};

}
}
}
#endif
