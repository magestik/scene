#include "ResourceManager.h"

#include "ResourceManagerListener.h"

#define _min(x, y) ((x < y) ? x : y)
#define _max(x, y) ((x > y) ? x : y)

/**
 * @brief Constructor
 */
ResourceManager::ResourceManager(void)
{
	m_iMeshCount = 0;
	m_iTextureCount = 0;
}

/**
 * @brief Destructor
 */
ResourceManager::~ResourceManager(void)
{
	// ...
}

/**
 * @brief ResourceManager::registerListener
 * @param listener
 * @return
 */
bool ResourceManager::registerListener(ResourceManagerListener * listener)
{
	m_aListeners.push_back(listener);
	return(true);
}

/**
 * @brief ResourceManager::registerMesh
 * @return
 */
unsigned int ResourceManager::registerMesh(const VertexData & vertexData)
{
	unsigned int MeshID = 1 + m_iMeshCount;

	computeBoundingVolumes(vertexData);

	onMeshImported(MeshID, vertexData);

	++m_iMeshCount;

	return(MeshID);
}

/**
 * @brief ResourceManager::registerMesh
 * @return
 */
unsigned int ResourceManager::registerMesh(const VertexData & vertexData, const IndexData & indexData)
{
	unsigned int MeshID = 1 + m_iMeshCount;

	computeBoundingVolumes(vertexData);

	onMeshImported(MeshID, vertexData, indexData);

	++m_iMeshCount;

	return(MeshID);
}

/**
 * @brief ResourceManager::registerTexture
 * @return
 */
unsigned int ResourceManager::registerTexture(const TextureData1D & textureData)
{
	unsigned int TextureID = 1 + m_iTextureCount;

	onTextureImported(TextureID, textureData);

	++m_iTextureCount;

	return(TextureID);
}

/**
 * @brief ResourceManager::registerTexture
 * @return
 */
unsigned int ResourceManager::registerTexture(const TextureData2D & textureData)
{
	unsigned int TextureID = 1 + m_iTextureCount;

	onTextureImported(TextureID, textureData);

	++m_iTextureCount;

	return(TextureID);
}

/**
 * @brief ResourceManager::registerTexture
 * @return
 */
unsigned int ResourceManager::registerTexture(const TextureData3D & textureData)
{
	unsigned int TextureID = 1 + m_iTextureCount;

	onTextureImported(TextureID, textureData);

	++m_iTextureCount;

	return(TextureID);
}

/**
 * @brief Scene::onMeshImported
 */
void ResourceManager::onMeshImported(unsigned int MeshID, const VertexData & vertexData) const
{
	for (ResourceManagerListener * listener : m_aListeners)
	{
		listener->onMeshImported(*this, MeshID, vertexData);
	}
}

/**
 * @brief Scene::onMeshImported
 */
void ResourceManager::onMeshImported(unsigned int MeshID, const VertexData & vertexData, const IndexData & indexData) const
{
	for (ResourceManagerListener * listener : m_aListeners)
	{
		listener->onMeshImported(*this, MeshID, vertexData, indexData);
	}
}

/**
 * @brief Scene::onTextureImported
 */
void ResourceManager::onTextureImported(unsigned int TextureID, const TextureData1D & textureData) const
{
	for (ResourceManagerListener * listener : m_aListeners)
	{
		listener->onTextureImported(*this, TextureID, textureData);
	}
}

/**
 * @brief Scene::onTextureImported
 */
void ResourceManager::onTextureImported(unsigned int TextureID, const TextureData2D & textureData) const
{
	for (ResourceManagerListener * listener : m_aListeners)
	{
		listener->onTextureImported(*this, TextureID, textureData);
	}
}

/**
 * @brief Scene::onTextureImported
 */
void ResourceManager::onTextureImported(unsigned int TextureID, const TextureData3D & textureData) const
{
	for (ResourceManagerListener * listener : m_aListeners)
	{
		listener->onTextureImported(*this, TextureID, textureData);
	}
}

/**
 * @brief ResourceManager::computeBoundingVolumes
 * @param vertexData
 */
void ResourceManager::computeBoundingVolumes(const VertexData & vertexData)
{
	vec3 * vertices = (vec3*)vertexData.vertices;

	//
	// Compute Bounding Box
	BoundingBox box;

	box.min = vec3(1e10f, 1e10f, 1e10f);
	box.max = vec3(-1e10f, -1e10f, -1e10f);

	for (int i = 0; i < vertexData.vertexCount; ++i)
	{
		box.min.x = _min(box.min.x, vertices[i].x);
		box.min.y = _min(box.min.y, vertices[i].y);
		box.min.z = _min(box.min.z, vertices[i].z);

		box.max.x = _max(box.max.x, vertices[i].x);
		box.max.y = _max(box.max.y, vertices[i].y);
		box.max.z = _max(box.max.z, vertices[i].z);
	}

	//
	// Compute Bounding Sphere
	BoundingSphere sphere;

	sphere.center.x = (box.max.x - box.min.x) * 0.5f;
	sphere.center.y = (box.max.y - box.min.y) * 0.5f;
	sphere.center.z = (box.max.z - box.min.z) * 0.5f;

	sphere.radius = _max(distance(sphere.center, box.min), distance(sphere.center, box.max));

	//
	// Save volumes
	m_aBoundingBoxes.push_back(box);
	m_aBoundingSpheres.push_back(sphere);
}

/**
 * @brief ResourceManager::getBoundingBox
 * @param MeshID
 * @return
 */
const BoundingBox & ResourceManager::getBoundingBox(unsigned int MeshID) const
{
	return(m_aBoundingBoxes[MeshID-1]);
}

/**
 * @brief ResourceManager::getBoundingSphere
 * @param MeshID
 * @return
 */
const BoundingSphere & ResourceManager::getBoundingSphere(unsigned int MeshID) const
{
	return(m_aBoundingSpheres[MeshID-1]);
}
