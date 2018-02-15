#pragma once

#include "ResourceData.h"

class ResourceManager;

class ResourceManagerListener
{
public:

	virtual void onMeshImported		(const ResourceManager & scene, unsigned int MeshID, const VertexData & vertexData) = 0;
	virtual void onMeshImported		(const ResourceManager & scene, unsigned int MeshID, const VertexData & vertexData, const IndexData & indexData) = 0;

	virtual void onTextureImported	(const ResourceManager & scene, unsigned int TextureID, const TextureData1D & textureData) = 0;
	virtual void onTextureImported	(const ResourceManager & scene, unsigned int TextureID, const TextureData2D & textureData) = 0;
	virtual void onTextureImported	(const ResourceManager & scene, unsigned int TextureID, const TextureData3D & textureData) = 0;
};
