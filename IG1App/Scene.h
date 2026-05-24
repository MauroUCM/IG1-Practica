#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "SingleColorEntity.h"
#include "RegularPolygon.h"
#include "RGBTriangle.h"
#include "RGBRectangle.h"
#include "Cube.h"
#include "Ground.h"
#include "BoxOutline.h"
#include "Star3D.h"
#include "GlassParapet.h"
#include "Torus.h"
#include "IndexMesh.h"
#include "IndexedBox.h"
#include "Sphere.h"
#include "Cone.h"
#include "Disk.h"
#include "SphereWithTexture.h"
#include "Droid.h"
#include "Light.h"

#include <vector>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene();

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init() = 0;

	void render(Camera const& cam) const;
	void uploadLights(Camera const& cam) const;
	virtual void update();
	void toggleLight();
	virtual void manageKey(unsigned int key) {};

	// load or unload scene data into the GPU
	void load();
	void unload();

	// droid control
	virtual void rotate() {};
	virtual void orbit() {};

protected:
	void destroy();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Light*> gLights;
};

class Scene0 : public Scene {

	void init() override;
};

class Scene1 : public Scene {

	void init() override;
};

class Scene2 : public Scene {

	void init() override;
};

class Scene3 : public Scene {

	void init() override;
};

class Scene4 : public Scene {

	void init() override;
};

class Scene5 : public Scene {

	void init() override;
};

class Scene6 : public Scene {

	void init() override;
};

class Scene7 : public Scene {

	void init() override;
};

class Scene8 : public Scene {
public:
	void init() override;

	// droid control
	void rotate() override;
	void orbit() override;

private:
	CompoundEntity* _node = nullptr;
	Droid* _droid;
	PosLight posLight;
};

class Scene9 : public Scene {

	void init() override;
};

#endif //_H_Scene_H_
