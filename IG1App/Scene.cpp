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
Scene::init()
{
	setGL(); // OpenGL settings

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	// Lights of the scene
	DirLight* dirLight = new DirLight(0);
	dirLight->setDirection(glm::vec3(-1.0f, -1.0f, -1.0f));
	dirLight->setAmb(glm::vec3(0.25f));
	dirLight->setDiff(glm::vec3(0.5f));
	dirLight->setSpec(glm::vec3(0.2f, 0.2f, 0.2f));
	dirLight->setEnabled(true);

	gLights.push_back(dirLight);
}

void
Scene::destroy()
{ // release memory and resources

	for (Abs_Entity* el : gObjects)
		delete el;

	gObjects.clear();
	gLights.clear();
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

	Shader* shad = Shader::get("light");
	shad->use();
	for (Light* obj : gLights)
		obj->unload(*shad);
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
	uploadLights(cam);

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
Scene::uploadLights(Camera const& cam) const {
	Shader* shader = Shader::get("light");
	shader->use();
	for (Light* lig : gLights) 
		lig->upload(*shader, cam.viewMat());
}

void
Scene::toggleLight() {
	for (Light* lig : gLights) lig->setEnabled(!lig->enabled());
}

void
Scene0::init() {
	Scene::init();
}

void
Scene1::init() {
	Scene::init();

	gObjects.push_back(new RegularPolygon(6, 200.0, { 1.0, 0.0, 1.0, 1.0 }));	// hexagono magenta
	gObjects.push_back(new RegularPolygon(60, 200.0, { 1.0, 1.0, 0.0, 1.0 }));	// circunferencia amarilla
}

void
Scene2::init() {
	Scene::init();

	gObjects.push_back(new RegularPolygon(60, 200.0, { 1.0, 0.0, 1.0, 1.0 }));	// circunferencia amarilla
	gObjects.push_back(new RGBRectangle(282.0, 282.0));							// rectangulo rgb
	gObjects.push_back(new RGBTriangle(80));									// triangulo rgb
}

void
Scene3::init() {
	Scene::init();

	gObjects.push_back(new Cube(100));
}

void
Scene4::init() {
	Scene::init();

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
	Scene::init();

	// Toro
	gObjects.push_back(new Torus(200, 75));
}

void
Scene6::init() {
	Scene::init();

	// Cube 4kHD
	gObjects.push_back(new IndexedBox(200));
}

void
Scene7::init() {
	Scene::init();

	// Droid
	gObjects.push_back(new Droid(100));
}

void
Scene8::init() {
	Scene::init();

	// radius variables
	GLdouble droidRad = 20,
		dathomirRad = 250;

	// invented node
	gNode = new CompoundEntity();
	gObjects.push_back(gNode);

	// Droid
	gDroid = new Droid(droidRad);
	glm::mat4 droidMat = gDroid->modelMat() * glm::translate(glm::mat4(1), glm::vec3(0, dathomirRad + droidRad * 0.75, 0));
	gDroid->setModelMat(droidMat);
	gNode->addEntity(gDroid);

	// Dathomir
	Sphere* dathomir = new Sphere(250, 30, 30);
	dathomir->SetColor({ 0.67, 0.13, 0.28, 1.0 });
	gObjects.push_back(dathomir);

	// posLight 
	gPosLight = new PosLight(0);
	gPosLight->setPosition(glm::uvec3(dathomirRad + 60, dathomirRad + 60, 0.0));
	gPosLight->setSpec(glm::vec3(0.2f, 0.2f, 0.2f));
	gPosLight->setAmb(glm::vec3(0.25f));
	gLights.push_back(gPosLight);

	// spotLight
	gSpotLight = new SpotLight(glm::uvec3(0, dathomirRad + 60, dathomirRad + 60), 0);
	gSpotLight->setDirection(glm::vec3(-1.0f, -1.0f, -1.0f));
	gSpotLight->setAmb(glm::vec3(0.25f));
	gSpotLight->setDiff(glm::vec3(0.5f));
	gSpotLight->setSpec(glm::vec3(0.2f, 0.2f, 0.2f));
	gLights.push_back(gSpotLight);
}

bool
Scene8::handleKey(unsigned int key) {
	bool redisplay = false;
	if (key == 'f') {	// rotate droid
		gNode->setModelMat(glm::rotate(gNode->modelMat(), glm::radians(5.0f), { 0.0,1.0,0.0 }));
		redisplay = true;
	}
	else if (key == 'g') {	// orbit droid
		GLfloat comm = 2.0f;
		gDroid->rollBall(comm * 10);
		glm::mat4 nodeMat = glm::rotate(gNode->modelMat(), glm::radians(comm), glm::vec3(1, 0, 0));
		gNode->setModelMat(nodeMat);
		redisplay = true;
	}
	else if (key == 't') { // toggle posLight
		gPosLight->setEnabled(!gPosLight->enabled());
		redisplay = true;
	}
	else if (key == 'y') {	// toggle spotLight
		gSpotLight->setEnabled(!gSpotLight->enabled());
		redisplay = true;
	}
	else if (key == 'h') {	// toggle droid light
		gDroid->toggleLight();
		redisplay = true;
	}
}

void
Scene9::init() {
	Scene::init();

	// yellow planet
	Sphere* yPlantet = new Sphere(75, 30, 30);
	yPlantet->SetColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	yPlantet->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(150, 0, 0)));
	gObjects.push_back(yPlantet);

	// gold planet
	Sphere* gPlanet = new Sphere(75, 30, 30);
	gPlanet->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 150)));
	gPlanet->getMaterial()->setGold();
	gObjects.push_back(gPlanet);

}