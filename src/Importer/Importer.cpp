#include "Importer.h"

#include "Scene.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <FreeImage.h>

#define ASSIMP_MAT4X4(m) mat4x4(m.a1, m.a2, m.a3, m.a4, m.b1, m.b2, m.b3, m.b4, m.c1, m.c2, m.c3, m.c4, m.d1, m.d2, m.d3, m.d4);

#define _min(x, y) ((x < y) ? x : y)
#define _max(x, y) ((x > y) ? x : y)

static const aiTextureType aSupportedTextureTypes [] = { aiTextureType_DIFFUSE, aiTextureType_SPECULAR, aiTextureType_NORMALS };

/**
 * @brief Constructor
 * @param szFilename
 */
Importer::Importer(const char * szFilename) : m_szFilename(szFilename), m_pLoadedScene(nullptr)
{
	FreeImage_Initialise();
}

/**
 * @brief Destructor
 */
Importer::~Importer(void)
{
	FreeImage_DeInitialise();
}

/**
 * @brief Importer::importToScene
 * @param scene
 * @return
 */
bool Importer::importToScene(Scene & scene)
{
	Assimp::Importer importer;
	m_pLoadedScene = importer.ReadFile(m_szFilename, aiProcessPreset_TargetRealtime_MaxQuality);

	if (!m_pLoadedScene)
	{
		return(false);
	}

	if (m_pLoadedScene->HasCameras())
	{
		importCameras(scene);
	}

	if (m_pLoadedScene->HasLights())
	{
		importLights(scene);
	}

	if (m_pLoadedScene->HasTextures())
	{
		importTextures(scene);
	}

	if (m_pLoadedScene->HasMaterials())
	{
		importMaterials(scene);
	}

	if (m_pLoadedScene->HasMeshes())
	{
		importMeshes(scene);
	}

	return(importObjects(scene));
}

/**
 * @brief Importer::importCameras
 * @param scene
 * @return
 */
bool Importer::importCameras(Scene & scene)
{
	for (int i = 0; i < m_pLoadedScene->mNumCameras; ++i)
	{
		aiCamera * camera = m_pLoadedScene->mCameras[i];

		const aiVector3D pos = camera->mPosition;
		const aiVector3D center = camera->mLookAt;
		const aiVector3D up = camera->mUp;

		Camera newCamera;
		newCamera.LookAt(vec3(pos.x, pos.y, pos.z), vec3(center.x, center.y, center.z), vec3(up.x, up.y, up.z));

		scene.insert(newCamera);
	}

	return(true);
}

/**
 * @brief Importer::importLights
 * @param scene
 * @return
 */
bool Importer::importLights(Scene & scene)
{
	for (int i = 0; i < m_pLoadedScene->mNumLights; ++i)
	{
		aiLight * light = m_pLoadedScene->mLights[i];

		switch (light->mType)
		{
			case aiLightSource_DIRECTIONAL:
			{
				// TODO
			}
			break;

			case aiLightSource_POINT:
			{
				// TODO
			}
			break;

			case aiLightSource_SPOT:
			{
				// TODO
			}
			break;

			case aiLightSource_AMBIENT:
			{
				// TODO
			}
			break;

			case aiLightSource_AREA:
			{
				// TODO
			}
			break;

			default:
			{
				assert(false);
			}
		}
	}

	return(true);
}

/**
 * @brief Importer::importTextures
 * @param scene
 * @return
 */
bool Importer::importTextures(Scene & scene)
{
	for (int i = 0; i < m_pLoadedScene->mNumTextures; ++i)
	{
		aiTexture * texture = m_pLoadedScene->mTextures[i];

		if (texture->mWidth > 0 && texture->mHeight > 0)
		{
			TextureData2D textureData;
			textureData.width = texture->mWidth;
			textureData.height = texture->mHeight;
			textureData.data = texture->pcData;
			textureData.texelFormat = TEXEL_FORMAT_RGBA8;

			scene.getResourceManager().registerTexture(textureData);
		}
		else
		{
			// TODO : compressed texture
		}
	}

	return(true);
}

/**
 * @brief Importer::importMaterials
 * @param scene
 * @return
 */
bool Importer::importMaterials(Scene & scene)
{
	for (int i = 0; i < m_pLoadedScene->mNumMaterials; ++i)
	{
		aiMaterial * material = m_pLoadedScene->mMaterials[i];

		for (aiTextureType type : aSupportedTextureTypes)
		{
			aiString str;
			material->GetTexture(type, 0, &str);

			FIBITMAP * dib = FreeImage_Load(FIF_PNG, str.C_Str());

			unsigned int bpp = FreeImage_GetBPP(dib);

			unsigned int width = FreeImage_GetWidth(dib);
			unsigned int height = FreeImage_GetHeight(dib);

			void * data = FreeImage_GetBits(dib);

			unsigned int TextureID = 0;

			if (bpp == 8)
			{
				TextureData2D textureData;
				textureData.width = width;
				textureData.height = height;
				textureData.data = data;
				textureData.texelFormat = TEXEL_FORMAT_RGBA8;

				TextureID = scene.getResourceManager().registerTexture(textureData);
			}
			else
			{
				// TODO : handle other formats
			}

			m_aTextureIDs.push_back(TextureID);

			FreeImage_Unload(dib);
		}
	}

	return(true);
}

/**
 * @brief Importer::importMeshes
 * @param scene
 * @return
 */
bool Importer::importMeshes(Scene & scene)
{
	m_aMeshIDs.reserve(m_pLoadedScene->mNumMeshes);

	for (int i = 0; i < m_pLoadedScene->mNumMeshes; ++i)
	{
		aiMesh * mesh = m_pLoadedScene->mMeshes[i];

		VertexData vertexData;
		vertexData.vertexCount = mesh->mNumVertices;

		unsigned int index = 0;

		if (mesh->HasPositions())
		{
			vertexData.vertexFormat[index] = VERTEX_FORMAT_FLOAT3;
			vertexData.vertexType[index] = VertexData::VERTEX_TYPE_POSITION;
			vertexData.vertices[index] = mesh->mVertices;
			++index;
		}

		if (mesh->HasNormals())
		{
			vertexData.vertexFormat[index] = VERTEX_FORMAT_FLOAT3;
			vertexData.vertexType[index] = VertexData::VERTEX_TYPE_NORMAL;
			vertexData.vertices[index] = mesh->mNormals;
			++index;
		}

		if (mesh->HasTangentsAndBitangents())
		{
			vertexData.vertexFormat[index] = VERTEX_FORMAT_FLOAT3;
			vertexData.vertexType[index] = VertexData::VERTEX_TYPE_TANGENT;
			vertexData.vertices[index] = mesh->mTangents;
			++index;

			vertexData.vertexFormat[index] = VERTEX_FORMAT_FLOAT3;
			vertexData.vertexType[index] = VertexData::VERTEX_TYPE_BITANGENT;
			vertexData.vertices[index] = mesh->mBitangents;
			++index;
		}

		if (mesh->HasVertexColors(0))
		{
			vertexData.vertexFormat[index] = VERTEX_FORMAT_FLOAT4;
			vertexData.vertexType[index] = VertexData::VERTEX_TYPE_COLOR0;
			vertexData.vertices[index] = mesh->mColors[0];
			++index;
		}

		if (mesh->HasTextureCoords(0))
		{
			vertexData.vertexFormat[index] = VERTEX_FORMAT_FLOAT4;
			vertexData.vertexType[index] = VertexData::VERTEX_TYPE_COLOR0;
			vertexData.vertices[index] = mesh->mTextureCoords[0];
			++index;
		}

		unsigned int MeshID = 0;

		if (mesh->HasFaces())
		{
			std::vector<unsigned int> indices;
			indices.reserve(mesh->mNumFaces);

			// Populate the index buffer
			for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
			{
				const aiFace & Face = mesh->mFaces[j];
				indices.push_back(Face.mIndices[0]);
				indices.push_back(Face.mIndices[1]);
				indices.push_back(Face.mIndices[2]);
			}

			IndexData indexData;
			indexData.indexCount = mesh->mNumFaces;
			indexData.indexFormat = INDEX_FORMAT_UINT32;
			indexData.indices = indices.data();

			MeshID = scene.getResourceManager().registerMesh(vertexData, indexData);
		}
		else
		{
			MeshID = scene.getResourceManager().registerMesh(vertexData);
		}

		m_aMeshIDs.push_back(MeshID);
	}

	return(true);
}

/**
 * @brief addMeshRecursive
 * @param nd
 * @param parentTransformation
 * @param scene
 */
static void addMeshRecursive(const aiNode * nd, const mat4x4 & parentTransformation, const std::vector<unsigned int> aMeshIDs, const std::vector<unsigned int> aTextureIDs, const aiScene * pLoadedScene, Scene & scene)
{
	const mat4x4 transformation = parentTransformation * ASSIMP_MAT4X4(nd->mTransformation);

	Object instance;

	instance.transformation = transformation;

	for (int i = 0; i < nd->mNumMeshes; ++i)
	{
		const unsigned int meshIndex = nd->mMeshes[i];
		aiMesh * pLoadedMesh = pLoadedScene->mMeshes[meshIndex];

		const unsigned int materialIndex = pLoadedMesh->mMaterialIndex;
		aiMaterial * pLoadedMaterial = pLoadedScene->mMaterials[materialIndex];

		Object::Mesh mesh;
		mesh.MeshID = aMeshIDs[meshIndex];

		//
		// Diffuse Texture
		{
			aiString str;
			pLoadedMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);
			mesh.DiffuseMapID = 0; // FIXME
		}

		//
		// Specular Texture
		{
			aiString str;
			pLoadedMaterial->GetTexture(aiTextureType_SPECULAR, 0, &str);
			mesh.SpecularMapID = 0; // FIXME
		}

		//
		// Shininess
		{
			mesh.shininess = 0.0f; // FIXME
		}

		//
		// Specular Texture
		{
			aiString str;
			pLoadedMaterial->GetTexture(aiTextureType_NORMALS, 0, &str);
			mesh.NormalMapID = 0; // FIXME
		}

		instance.Meshes.push_back(mesh);
	}

	scene.insert(instance);

	for (int i = 0; i < nd->mNumChildren; ++i)
	{
		addMeshRecursive(nd->mChildren[i], transformation, aMeshIDs, aTextureIDs, pLoadedScene, scene);
	}
}

/**
 * @brief Importer::importObjects
 * @param scene
 * @return
 */
bool Importer::importObjects(Scene & scene)
{
	const mat4x4 identity (1.0f);

	addMeshRecursive(m_pLoadedScene->mRootNode, identity, m_aMeshIDs, m_aTextureIDs, m_pLoadedScene, scene);

	return(true);
}
