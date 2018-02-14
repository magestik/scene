#pragma once

#include <vector>

#include "ResourceFormats.h"

class ResourceManagerListener;

class ResourceManager
{
public:

	ResourceManager(void);
	~ResourceManager(void);

	bool registerListener(ResourceManagerListener * listener);

	unsigned int registerMesh		(unsigned int vertexCount, void ** vertices, VertexFormat vertexFormat);
	unsigned int registerMesh		(unsigned int vertexCount, void ** vertices, VertexFormat vertexFormat, unsigned int indexCount, void * indexes, IndexFormat indexFormat);

	unsigned int registerTexture	(unsigned int width, void * data, TexelFormat texelFormat);
	unsigned int registerTexture	(unsigned int width, unsigned int height, void * data, TexelFormat texelFormat);
	unsigned int registerTexture	(unsigned int width, unsigned int height, unsigned int depth, void * data, TexelFormat texelFormat);

private:

	void onMeshImported(unsigned int MeshID, unsigned int vertexCount, void ** vertices, VertexFormat vertexFormat) const;
	void onMeshImported(unsigned int MeshID, unsigned int vertexCount, void ** vertices, VertexFormat vertexFormat, unsigned int indexCount, void * indexes, IndexFormat indexFormat) const;

	void onTextureImported(unsigned int TextureID, unsigned int width, void * data, TexelFormat texelFormat) const;
	void onTextureImported(unsigned int TextureID, unsigned int width, unsigned int height, void * data, TexelFormat texelFormat) const;
	void onTextureImported(unsigned int TextureID, unsigned int width, unsigned int height, unsigned int depth, void * data, TexelFormat texelFormat) const;

private:

	unsigned int m_iMeshCount;
	unsigned int m_iTextureCount;

	std::vector<ResourceManagerListener*> m_aListeners;
};
