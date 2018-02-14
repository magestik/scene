#pragma once

#include "ResourceFormats.h"

class ResourceManager;

class ResourceManagerListener
{
public:

	virtual void onMeshImported		(const ResourceManager & scene, unsigned int MeshID, unsigned int vertexCount, void ** vertices, VertexFormat vertexFormat) = 0;
	virtual void onMeshImported		(const ResourceManager & scene, unsigned int MeshID, unsigned int vertexCount, void ** vertices, VertexFormat vertexFormat, unsigned int indexCount, void * indexes, IndexFormat indexFormat) = 0;

	virtual void onTextureImported	(const ResourceManager & scene, unsigned int TextureID, unsigned int width, void * data, TexelFormat texelFormat) = 0;
	virtual void onTextureImported	(const ResourceManager & scene, unsigned int TextureID, unsigned int width, unsigned int height, void * data, TexelFormat texelFormat) = 0;
	virtual void onTextureImported	(const ResourceManager & scene, unsigned int TextureID, unsigned int width, unsigned int height, unsigned int depth, void * data, TexelFormat texelFormat) = 0;
};
