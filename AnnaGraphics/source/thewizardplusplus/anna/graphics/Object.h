#ifndef OBJECT_H
#define OBJECT_H

#include "../maths/Vector3D.h"
#include <vector>

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class Mesh;

class Object {
public:
	static Object* loadFromFile(const std::string& filename);

	Object(void);
	virtual ~Object(void);
	size_t getNumberOfMeshes(void) const;
	Mesh* getMesh(size_t number) const;
	void addMesh(Mesh* mesh);
	void removeMesh(Mesh* mesh);
	maths::Vector3D<float> getPosition(void) const;
	void setPosition(const maths::Vector3D<float>& position);
	void setPosition(float x, float y, float z);
	maths::Vector3D<float> getRotation(void) const;
	void setRotation(const maths::Vector3D<float>& rotation);
	void setRotation(float x, float y, float z);
	maths::Vector3D<float> getScale(void) const;
	void setScale(const maths::Vector3D<float>& scale);
	void setScale(float x, float y, float z);
	bool isVisible(void) const;
	void setVisible(bool visible);

protected:
	typedef std::vector<Mesh*> MeshVector;

	MeshVector             meshes;
	maths::Vector3D<float> position;
	maths::Vector3D<float> rotation;
	maths::Vector3D<float> scale;
	bool                   visible;
};

}
}
}
#endif
