#include "ResourceManager.h"

#include "ResourceManagerListener.h"

/**
 * @brief Constructor
 */
ResourceManager::ResourceManager(void)
{
	// ...
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
