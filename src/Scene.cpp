#include "Scene.h"

#include "SceneListener.h"

#include "Importer/Importer.h"

#define _min(x, y) ((x < y) ? x : y)
#define _max(x, y) ((x > y) ? x : y)

static inline vec3 _transform(const vec3 & point, const mat4x4 & matTransform)
{
	vec4 transformed = matTransform * vec4(point, 1.0f);
	return(transformed.xyz / transformed.w);
}

/**
 * @brief Scene::Scene
 */
Scene::Scene(void)
{
	m_pLight = new Light::Directionnal(vec3(-20.0f, -20.0f, -20.0f));
	m_vAmbientColor = vec3(0.0f, 0.0f, 0.0f);

	m_BoundingBox.min = vec3(0.0f, 0.0f, 0.0f);
	m_BoundingBox.max = vec3(0.0f, 0.0f, 0.0f);

	m_BoundingSphere.center = vec3(0.0f, 0.0f, 0.0f);
	m_BoundingSphere.radius = 0.0f;
}

/**
 * @brief Scene::~Scene
 */
Scene::~Scene(void)
{
	delete m_pLight;
}

/**
 * @brief Scene::registerListener
 * @param listener
 * @return
 */
bool Scene::registerListener(SceneListener * listener)
{
	m_aListeners.push_back(listener);
	return(true);
}

/**
 * @brief Scene::import
 * @param szFilename
 * @return
 */
bool Scene::import(const char * szFilename)
{
	Importer importer(szFilename);

	if (!importer.importToScene(*this))
	{
		return(false);
	}

	return(computeBoundingVolumes());
}

/**
 * @brief Scene::insert
 * @param object
 * @return
 */
bool Scene::insert(const Object & object)
{
	m_aObjects.push_back(object);
	onObjectInserted(object);
	return(true);
}

/**
 * @brief Scene::remove
 * @param object
 * @return
 */
bool Scene::remove(const Object & object)
{
	for (std::vector<Object>::iterator it = m_aObjects.begin() ; it != m_aObjects.end(); ++it)
	{
		const Object & current = *it;

		if (&current == &object)
		{
			m_aObjects.erase(it);
			onObjectRemoved(object);
			return(true);
		}
	}

	return(false);
}

/**
 * @brief Scene::insert
 * @param camera
 * @return
 */
bool Scene::insert(const Camera & camera)
{
	m_aCameras.push_back(camera);
	onCameraInserted(camera);
	return(true);
}

/**
 * @brief Scene::remove
 * @param camera
 * @return
 */
bool Scene::remove(const Camera & camera)
{
	for (std::vector<Camera>::iterator it = m_aCameras.begin() ; it != m_aCameras.end(); ++it)
	{
		const Camera & current = *it;

		if (&current == &camera)
		{
			m_aCameras.erase(it);
			onCameraRemoved(camera);
			return(true);
		}
	}

	return(false);
}

/**
 * @brief Scene::onObjectInserted
 */
void Scene::onObjectInserted(const Object & object) const
{
	for (SceneListener * listener : m_aListeners)
	{
		listener->onObjectInserted(*this, object);
	}
}

/**
 * @brief Scene::onObjectRemoved
 */
void Scene::onObjectRemoved(const Object & object) const
{
	for (SceneListener * listener : m_aListeners)
	{
		listener->onObjectRemoved(*this, object);
	}
}

/**
 * @brief Scene::onCameraInserted
 * @param object
 */
void Scene::onCameraInserted(const Camera & camera) const
{
	for (SceneListener * listener : m_aListeners)
	{
		listener->onCameraInserted(*this, camera);
	}
}

/**
 * @brief Scene::onCameraRemoved
 * @param object
 */
void Scene::onCameraRemoved(const Camera & camera) const
{
	for (SceneListener * listener : m_aListeners)
	{
		listener->onCameraRemoved(*this, camera);
	}
}

/**
 * @brief Scene::updateBoundingVolumes
 */
bool Scene::computeBoundingVolumes(void)
{
	vec3 vMin(+INFINITY, +INFINITY, +INFINITY);
	vec3 vMax(-INFINITY, -INFINITY, -INFINITY);

	for (const Object & object : m_aObjects)
	{
		for (const Object::Mesh & mesh : object.Meshes)
		{
			const BoundingBox & box = m_resourcesManager.getBoundingBox(mesh.MeshID);

			vec3 points [8] =
			{
				vec3(box.min.x, box.min.y, box.min.z),
				vec3(box.max.x, box.min.y, box.min.z),
				vec3(box.min.x, box.max.y, box.min.z),
				vec3(box.max.x, box.max.y, box.min.z),
				vec3(box.min.x, box.min.y, box.max.z),
				vec3(box.max.x, box.min.y, box.max.z),
				vec3(box.min.x, box.max.y, box.max.z),
				vec3(box.max.x, box.max.y, box.max.z),
			};

			for (const vec3 point : points)
			{
				vec3 WorldPoint = _transform(point, object.transformation);

				//
				// Min
				if (WorldPoint.x < vMin.x)
				{
					vMin.x = WorldPoint.x;
				}

				if (WorldPoint.y < vMin.y)
				{
					vMin.y = WorldPoint.y;
				}

				if (WorldPoint.z < vMin.z)
				{
					vMin.z = WorldPoint.z;
				}

				//
				// Max
				if (WorldPoint.x > vMax.x)
				{
					vMax.x = WorldPoint.x;
				}

				if (WorldPoint.y > vMax.y)
				{
					vMax.y = WorldPoint.y;
				}

				if (WorldPoint.z > vMax.z)
				{
					vMax.z = WorldPoint.z;
				}
			}
		}
	}

	//
	// Update Bounding Box
	m_BoundingBox.min = vMin;
	m_BoundingBox.max = vMax;

	//
	// Update Bounding sphere
	m_BoundingSphere.center.x = (m_BoundingBox.max.x - m_BoundingBox.min.x) * 0.5f;
	m_BoundingSphere.center.y = (m_BoundingBox.max.y - m_BoundingBox.min.y) * 0.5f;
	m_BoundingSphere.center.z = (m_BoundingBox.max.z - m_BoundingBox.min.z) * 0.5f;

	m_BoundingSphere.radius = _max(distance(m_BoundingSphere.center, m_BoundingBox.min), distance(m_BoundingSphere.center, m_BoundingBox.max));

	return(true);
}

/**
 * @brief Scene::getBoundingBox
 * @return
 */
const BoundingBox & Scene::getBoundingBox(void) const
{
	return(m_BoundingBox);
}

/**
 * @brief Scene::getBoundingSphere
 * @return
 */
const BoundingSphere & Scene::getBoundingSphere(void) const
{
	return(m_BoundingSphere);
}
