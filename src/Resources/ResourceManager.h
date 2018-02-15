#pragma once

#include <vector>

#include "ResourceData.h"

class ResourceManagerListener;

class ResourceManager
{
public:

	ResourceManager(void);
	~ResourceManager(void);

	bool registerListener(ResourceManagerListener * listener);

	unsigned int registerMesh		(const VertexData & vertexData);
	unsigned int registerMesh		(const VertexData & vertexData, const IndexData & indexData);

	unsigned int registerTexture	(const TextureData1D & textureData);
	unsigned int registerTexture	(const TextureData2D & textureData);
	unsigned int registerTexture	(const TextureData3D & textureData);

private:

	void onMeshImported(unsigned int MeshID, const VertexData & vertexData) const;
	void onMeshImported(unsigned int MeshID, const VertexData & vertexData, const IndexData & indexData) const;

	void onTextureImported(unsigned int TextureID, const TextureData1D & textureData) const;
	void onTextureImported(unsigned int TextureID, const TextureData2D & textureData) const;
	void onTextureImported(unsigned int TextureID, const TextureData3D & textureData) const;

private:

	unsigned int m_iMeshCount;
	unsigned int m_iTextureCount;

	std::vector<ResourceManagerListener*> m_aListeners;
};
