#pragma once

#include <vector>

#include "ResourceData.h"

#include "../Volumes/BoundingBox.h"
#include "../Volumes/BoundingSphere.h"

class ResourceManagerListener;

class ResourceManager
{
public:

	ResourceManager(void);
	~ResourceManager(void);

//--------------------------------------------------------------------------------------
//		Resources
//--------------------------------------------------------------------------------------

public:

	unsigned int registerMesh		(const VertexData & vertexData);
	unsigned int registerMesh		(const VertexData & vertexData, const IndexData & indexData);

	unsigned int registerTexture	(const TextureData1D & textureData);
	unsigned int registerTexture	(const TextureData2D & textureData);
	unsigned int registerTexture	(const TextureData3D & textureData);

private:

	unsigned int m_iMeshCount;
	unsigned int m_iTextureCount;

//--------------------------------------------------------------------------------------
//		Bounding Volumes
//--------------------------------------------------------------------------------------

public:

	const BoundingBox &		getBoundingBox		(unsigned int MeshID) const;
	const BoundingSphere &	getBoundingSphere	(unsigned int MeshID) const;

protected:

	void computeBoundingVolumes(const VertexData & vertexData);

private:

	std::vector<BoundingBox>	m_aBoundingBoxes;
	std::vector<BoundingSphere>	m_aBoundingSpheres;

//--------------------------------------------------------------------------------------
//		Listener
//--------------------------------------------------------------------------------------

public:

	bool registerListener(ResourceManagerListener * listener);

protected:

	void onMeshImported(unsigned int MeshID, const VertexData & vertexData) const;
	void onMeshImported(unsigned int MeshID, const VertexData & vertexData, const IndexData & indexData) const;

	void onTextureImported(unsigned int TextureID, const TextureData1D & textureData) const;
	void onTextureImported(unsigned int TextureID, const TextureData2D & textureData) const;
	void onTextureImported(unsigned int TextureID, const TextureData3D & textureData) const;

private:

	std::vector<ResourceManagerListener*> m_aListeners;

};
