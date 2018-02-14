#pragma once

class Scene;
class Object;
class Camera;

class SceneListener
{

public:

	virtual void onObjectInserted	(const Scene & scene, const Object & object) = 0;
	virtual void onObjectRemoved	(const Scene & scene, const Object & object) = 0;

	virtual void onCameraInserted	(const Scene & scene, const Camera & camera) = 0;
	virtual void onCameraRemoved	(const Scene & scene, const Camera & camera) = 0;

};
