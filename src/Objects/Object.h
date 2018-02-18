#pragma once

#include <Vector.h>
#include <Matrix.h>

#include <vector>

struct Object
{
	Object(void) : transformation(1.0f), Meshes() { /* ... */ }

	mat4x4 transformation;

	struct Mesh
	{
		Mesh(void)
		{
			MeshID = 0;
			DiffuseMapID = 0;
			SpecularMapID = 0;
			shininess = 0.0f;
			NormalMapID = 0;
		}

		unsigned int MeshID;

		// Diffuse color/texture
		vec3 Kd;
		unsigned int DiffuseMapID;

		// Specular color/texture
		vec3 Ks;
		unsigned int SpecularMapID;

		// Shininess
		float shininess;

		// Normal Map
		unsigned int NormalMapID;
	};

	std::vector<Mesh> Meshes;
};
