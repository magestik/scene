#pragma once

#include <Vector.h>
#include <Matrix.h>

#include <vector> // std::vector

class Mesh;

struct Object
{
	Object(Mesh * m) : transformation(1.0f), mesh(m) { /* ... */ }
	//const std::vector<SubMesh*> & getDrawCommands() const { return(mesh->m_aSubMeshes); }
	mat4x4 transformation;
	Mesh * mesh;
};
