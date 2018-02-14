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
unsigned int ResourceManager::registerMesh(unsigned int vertexCount, void ** vertices, VertexFormat vertexFormat)
{
	unsigned int MeshID = 1 + m_iMeshCount;

	onMeshImported(MeshID, vertexCount, vertices, vertexFormat);

	++m_iMeshCount;

	return(MeshID);
}

/**
 * @brief ResourceManager::registerMesh
 * @return
 */
unsigned int ResourceManager::registerMesh(unsigned int vertexCount, void ** vertices, VertexFormat vertexFormat, unsigned int indexCount, void * indexes, IndexFormat indexFormat)
{
	unsigned int MeshID = 1 + m_iMeshCount;

	onMeshImported(MeshID, vertexCount, vertices, vertexFormat, indexCount, indexes, indexFormat);

	++m_iMeshCount;

	return(MeshID);
}

/**
 * @brief ResourceManager::registerTexture
 * @return
 */
unsigned int ResourceManager::registerTexture(unsigned int width, void * data, TexelFormat texelFormat)
{
	unsigned int TextureID = 1 + m_iTextureCount;

	onTextureImported(TextureID, width, data, texelFormat);

	++m_iTextureCount;

	return(TextureID);
}

/**
 * @brief ResourceManager::registerTexture
 * @return
 */
unsigned int ResourceManager::registerTexture(unsigned int width, unsigned int height, void * data, TexelFormat texelFormat)
{
	unsigned int TextureID = 1 + m_iTextureCount;

	onTextureImported(TextureID, width, height, data, texelFormat);

	++m_iTextureCount;

	return(TextureID);
}

/**
 * @brief ResourceManager::registerTexture
 * @return
 */
unsigned int ResourceManager::registerTexture(unsigned int width, unsigned int height, unsigned int depth, void * data, TexelFormat texelFormat)
{
	unsigned int TextureID = 1 + m_iTextureCount;

	onTextureImported(TextureID, width, height, depth, data, texelFormat);

	++m_iTextureCount;

	return(TextureID);
}

/**
 * @brief Scene::onMeshImported
 */
void ResourceManager::onMeshImported(unsigned int MeshID, unsigned int vertexCount, void ** vertices, VertexFormat vertexFormat) const
{
	for (ResourceManagerListener * listener : m_aListeners)
	{
		listener->onMeshImported(*this, MeshID, vertexCount, vertices, vertexFormat);
	}
}

/**
 * @brief Scene::onMeshImported
 */
void ResourceManager::onMeshImported(unsigned int MeshID, unsigned int vertexCount, void ** vertices, VertexFormat vertexFormat, unsigned int indexCount, void * indexes, IndexFormat indexFormat) const
{
	for (ResourceManagerListener * listener : m_aListeners)
	{
		listener->onMeshImported(*this, MeshID, vertexCount, vertices, vertexFormat, indexCount, indexes, indexFormat);
	}
}

/**
 * @brief Scene::onTextureImported
 */
void ResourceManager::onTextureImported(unsigned int TextureID, unsigned int width, void * data, TexelFormat texelFormat) const
{
	for (ResourceManagerListener * listener : m_aListeners)
	{
		listener->onTextureImported(*this, TextureID, width, data, texelFormat);
	}
}

/**
 * @brief Scene::onTextureImported
 */
void ResourceManager::onTextureImported(unsigned int TextureID, unsigned int width, unsigned int height, void * data, TexelFormat texelFormat) const
{
	for (ResourceManagerListener * listener : m_aListeners)
	{
		listener->onTextureImported(*this, TextureID, width, height, data, texelFormat);
	}
}

/**
 * @brief Scene::onTextureImported
 */
void ResourceManager::onTextureImported(unsigned int TextureID, unsigned int width, unsigned int height, unsigned int depth, void * data, TexelFormat texelFormat) const
{
	for (ResourceManagerListener * listener : m_aListeners)
	{
		listener->onTextureImported(*this, TextureID, width, height, depth, data, texelFormat);
	}
}
