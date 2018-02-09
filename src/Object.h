#pragma once

#include <Vector.h>
#include <Matrix.h>

class Mesh;

struct Object
{
	Object(Mesh * m) : transformation(1.0f), mesh(m) { /* ... */ }
	mat4x4 transformation;
	Mesh * mesh;
};
