#pragma once

class Scene;

class Importer
{
public:

	Importer(const char * szFilename);
	~Importer(void);

	bool importToScene(Scene & scene) const;

};
