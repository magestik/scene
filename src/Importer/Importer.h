#pragma once

#include <vector>
#include <map>

class Scene;

class Importer
{
public:

	Importer(const char * szFilename);
	~Importer(void);

	bool importToScene(Scene & scene);

protected:

	bool importCameras(Scene & scene);
	bool importLights(Scene & scene);
	bool importTextures(Scene & scene);
	bool importMaterials(Scene & scene);
	bool importMeshes(Scene & scene);

	bool importObjects(Scene & scene);

private:

	const char * m_szFilename;

	const struct aiScene * m_pLoadedScene;

	std::vector<unsigned int> m_aMeshIDs;
	std::map<std::string, unsigned int> m_aTextureIDs;
};
