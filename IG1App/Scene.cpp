#include "Scene.h"
#include "ColorMaterialEntity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;

Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	for (Abs_Entity* el : gObjects)
		delete el;

	gObjects.clear();
}

void
Scene::load()
{
	for (Abs_Entity* obj : gObjects)
		obj->load();
}

void
Scene::unload()
{
	for (Abs_Entity* obj : gObjects)
		obj->unload();
}

void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());
}

void
Scene::update() {
	for (Abs_Entity* obj : gObjects) {
		obj->update();
	}
}

void
Scene0::init() {
	setGL(); // OpenGL settings

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));	// ejes RGB
}

void
Scene1::init() {
	setGL(); // OpenGL settings

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));	// ejes RGB

	gObjects.push_back(new RegularPolygon(6, 200.0, { 1.0, 0.0, 1.0, 1.0 }));	// hexagono magenta
	gObjects.push_back(new RegularPolygon(60, 200.0, { 1.0, 1.0, 0.0, 1.0 }));	// circunferencia amarilla
}

void
Scene2::init() {
	setGL(); // OpenGL settings

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));	// ejes RGB

	gObjects.push_back(new RegularPolygon(60, 200.0, { 1.0, 0.0, 1.0, 1.0 }));	// circunferencia amarilla
	gObjects.push_back(new RGBRectangle(282.0, 282.0));							// rectangulo rgb
	gObjects.push_back(new RGBTriangle(80));									// triangulo rgb
}

void
Scene3::init() {
	setGL(); // OpenGL settings

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));	// ejes RGB

	gObjects.push_back(new Cube(100));
}

void
Scene4::init() {
	setGL(); // OpenGL settings

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));	// ejes RGB

	// 3D star
	Texture* sText = new Texture();
	sText->load("../assets/images/rueda.png");
	gObjects.push_back(new Star3D(30, 8, 30, sText));

	// Tiles
	Texture* gText = new Texture();
	gText->load("../assets/images/baldosaC.png");
	gText->setWrap(GL_REPEAT);
	gObjects.push_back(new Ground(gText));

	// Box
	Texture* boText = new Texture();
	boText->load("../assets/images/papelE.png");
	Texture* biText = new Texture();
	biText->load("../assets/images/container.jpg");
	gObjects.push_back(new BoxOutline(100.0, boText, biText));

	// Transparent border
	Texture* glText = new Texture();
	glText->load("../assets/images/windowC.png", 100U);
	glText->setWrap(GL_REPEAT);
	gObjects.push_back(new GlassParapet(500, glText));
}

void
Scene5::init() {
	setGL(); // OpenGL settings

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));	// ejes RGB

	// Toro
	gObjects.push_back(new Torus(200, 75));
}

void
Scene6::init() {
	setGL(); // OpenGL settings

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));	// ejes RGB

	// Cube 4kHD
	gObjects.push_back(new IndexedBox(200));
}

void
Scene7::init() {
	setGL(); // OpenGL settings

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));	// ejes RGB

	// Droid
	gObjects.push_back(new Droid(100));
}

void
Scene8::init() {
	setGL(); // OpenGL settings

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));	// ejes RGB

	// radius variables
	GLdouble droidRad = 20,
		dathomirRad = 250;

	// invented node
	_node = new CompoundEntity();
	gObjects.push_back(_node);

	// Droid
	_droid = new Droid(droidRad);
	glm::mat4 droidMat = _droid->modelMat() * glm::translate(glm::mat4(1), glm::vec3(0, dathomirRad + droidRad * 0.75, 0));
	_droid->setModelMat(droidMat);
	_node->addEntity(_droid);

	// Dathomir
	Sphere* dathomir = new Sphere(250, 30, 30);
	dathomir->SetColor({ 0.67, 0.13, 0.28, 1.0 });
	gObjects.push_back(dathomir);
}

void
Scene8::rotate() {
	_node->setModelMat(glm::rotate(_node->modelMat(), glm::radians(5.0f), { 0.0,1.0,0.0 }));
}

void
Scene8::orbit() {
	GLfloat comm = 2.0f;
	_droid->rollBall(comm * 10);
	glm::mat4 nodeMat = glm::rotate(_node->modelMat(), glm::radians(comm), glm::vec3(1, 0, 0));
	_node->setModelMat(nodeMat);
}