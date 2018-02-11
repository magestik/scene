#include "Importer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/**
 * @brief Constructor
 * @param szFilename
 */
Importer::Importer(const char * szFilename)
{
	// ...
}

/**
 * @brief Destructor
 */
Importer::~Importer(void)
{
	// ...
}

/**
 * @brief Importer::importToScene
 * @param scene
 * @return
 */
bool Importer::importToScene(Scene & scene) const
{
	return(false); // TODO
}
