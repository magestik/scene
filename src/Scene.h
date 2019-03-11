#pragma once

#include "Objects/Object.h"
#include "Objects/Camera/Camera.h"
#include "Objects/Light/Light.h"

#include "Volumes/BoundingBox.h"
#include "Volumes/BoundingSphere.h"

#include "Resources/ResourceManager.h"

#include <vector>

class SceneListener;

class Scene
{
public:

	Scene(void);
	~Scene(void);

//--------------------------------------------------------------------------------------
//		Objects
//--------------------------------------------------------------------------------------

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

public: //private:

	Light::Directionnal * m_pLight; // TODO : remove this

	vec3 m_vAmbientColor;

	struct Fog
	{
		Fog(void) : Color(0.8f, 0.8f, 0.8f), Scattering(0.35f), Extinction(0.35f)
		{
			// ...
		}

		vec3 Color;
		float Scattering;
		float Extinction;
	};

	Fog fog;

private:

	std::vector<Camera> m_aCameras;
	std::vector<Object> m_aObjects;

//--------------------------------------------------------------------------------------
//		Bounding Volumes
//--------------------------------------------------------------------------------------

public:

	bool					computeBoundingVolumes	(void);

	const BoundingBox &		getBoundingBox			(void) const;
	const BoundingSphere &	getBoundingSphere		(void) const;

private:

	BoundingBox		m_BoundingBox;
	BoundingSphere	m_BoundingSphere;

//--------------------------------------------------------------------------------------
//		Resource manager
//--------------------------------------------------------------------------------------

public:

	inline ResourceManager & getResourceManager(void)
	{
		return(m_resourcesManager);
	}

	inline const ResourceManager & getResourceManager(void) const
	{
		return(m_resourcesManager);
	}

private:

	ResourceManager m_resourcesManager;

//--------------------------------------------------------------------------------------
//		Listener
//--------------------------------------------------------------------------------------

public:

	bool registerListener(SceneListener * listener);

protected:

	void onObjectInserted(const Object & object) const;
	void onObjectRemoved(const Object & object) const;

	void onCameraInserted(const Camera & camera) const;
	void onCameraRemoved(const Camera & camera) const;

private:

	std::vector<SceneListener*> m_aListeners;

};
