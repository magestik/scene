#pragma once

#include <Vector.h>
#include <Matrix.h>

#include <vector>

struct Object
{
	Object(void) : transformation(1.0f), MeshIDs() { /* ... */ }
	mat4x4 transformation;
	std::vector<unsigned int> MeshIDs;
};
