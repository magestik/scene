#pragma once

#include <Vector.h>

struct BoundingBox
{
	BoundingBox(void) : min(1e10f, 1e10f, 1e10f), max(-1e10f, -1e10f, -1e10f) { /* ... */ }
	vec3 min;
	vec3 max;
};
