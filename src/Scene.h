#pragma once

#include "Object.h"
#include "Camera/Camera.h"
#include "Light/Light.h"

#include "ResourceManager.h"

#include <vector>

class SceneListener;

class Scene
{
public:

	Scene(void);
	~Scene(void);

	bool registerListener(SceneListener * listener);

	bool import(const char * szFilename);

	bool insert(const Object & object);
	bool remove(const Object & object);

	bool insert(const Camera & camera);
	bool remove(const Camera & camera);

	inline const std::vector<Object> & getObjects(void) const
	{
		return(m_aObjects);
	}

	inline unsigned int getObjectCount(void) const
	{
		return(m_aObjects.size());
	}

	inline ResourceManager & getResourceManager(void)
	{
		return(m_resourcesManager);
	}

private:

	void onObjectInserted(const Object & object) const;
	void onObjectRemoved(const Object & object) const;

	void onCameraInserted(const Camera & camera) const;
	void onCameraRemoved(const Camera & camera) const;

public: //private:

	Light::Directionnal * m_pLight;

private:

	ResourceManager m_resourcesManager;

	std::vector<Camera> m_aCameras;
	std::vector<Object> m_aObjects;

	std::vector<SceneListener*> m_aListeners;
};
