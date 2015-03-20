#include "Skybox.h"
#include "PlaneMesh.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

Skybox::Skybox(Texture* top, Texture* bottom, Texture* side1, Texture* side2,
	Texture* side3, Texture* side4)
{
	PlaneMesh* top_mesh = new PlaneMesh(this);
	top_mesh->setPosition(Vector3D<float>(0.0f, 0.0f, 1.0f));
	top_mesh->getMaterial().texture =             top;
	top_mesh->getMaterial().allow_ambient_light = false;
	top_mesh->getMaterial().allow_fog =           false;

	PlaneMesh* bottom_mesh = new PlaneMesh(this);
	bottom_mesh->setPosition(Vector3D<float>(0.0f, 0.0f, -1.0f));
	bottom_mesh->getMaterial().texture =             bottom;
	bottom_mesh->getMaterial().allow_ambient_light = false;
	bottom_mesh->getMaterial().allow_fog =           false;

	PlaneMesh* side1_mesh = new PlaneMesh(this);
	side1_mesh->setPosition(Vector3D<float>(0.0f, -1.0f, 0.0f));
	side1_mesh->setRotation(Vector3D<float>(90.0f, 0.0f, 0.0f));
	side1_mesh->getMaterial().texture =             side1;
	side1_mesh->getMaterial().allow_ambient_light = false;
	side1_mesh->getMaterial().allow_fog =           false;

	PlaneMesh* side2_mesh = new PlaneMesh(this);
	side2_mesh->setPosition(Vector3D<float>(1.0f, 0.0f, 0.0f));
	side2_mesh->setRotation(Vector3D<float>(-90.0f, -90.0f, 0.0f));
	side2_mesh->getMaterial().texture =             side2;
	side2_mesh->getMaterial().allow_ambient_light = false;
	side2_mesh->getMaterial().allow_fog =           false;

	PlaneMesh* side3_mesh = new PlaneMesh(this);
	side3_mesh->setPosition(Vector3D<float>(0.0f, 1.0f, 0.0f));
	side3_mesh->setRotation(Vector3D<float>(270.0f, 0.0f, 0.0f));
	side3_mesh->getMaterial().texture =             side3;
	side3_mesh->getMaterial().allow_ambient_light = false;
	side3_mesh->getMaterial().allow_fog =           false;

	PlaneMesh* side4_mesh = new PlaneMesh(this);
	side4_mesh->setPosition(Vector3D<float>(-1.0f, 0.0f, 0.0f));
	side4_mesh->setRotation(Vector3D<float>(90.0f, -90.0f, 0.0f));
	side4_mesh->getMaterial().texture =             side4;
	side4_mesh->getMaterial().allow_ambient_light = false;
	side4_mesh->getMaterial().allow_fog =           false;
}
