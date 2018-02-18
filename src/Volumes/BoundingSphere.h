#pragma once

#include <Vector.h>

struct BoundingSphere
{
	BoundingSphere(void) : center(0.0f, 0.0f, 0.0f), radius(0.0f) { /* ... */ }
	vec3 center;
	float radius;
};
