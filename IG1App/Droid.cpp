#include "Droid.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>

Droid::Droid(GLdouble radius) {
	// sphere
	Texture* baText = new Texture();
	baText->load("../assets/images/container.jpg");
	_ball = new SphereWithTexture(radius, 20, 20, baText);
	addEntity(_ball);

	// head
	_head = new Cone(radius/2, radius, radius/2, 10, 20);
	_head->SetColor({ 1, 1, 0, 1 });
	glm::mat4 auxMat = glm::translate(glm::mat4(1.0), glm::vec3(0, radius, 0));
	_head->setModelMat(auxMat);
	addEntity(_head);

	// eyes
	_eye1 = new Disk(radius / 2, radius / 15, 10, 20);
	auxMat = glm::translate(glm::mat4(1.0), glm::vec3(radius / 15, radius * 1.25, radius * 0.75))
		* glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(1, 0, 0));;
	_eye1->setModelMat(auxMat);
	addEntity(_eye1);

	_eye2 = new Disk(radius / 2, radius / 15, 10, 20);
	auxMat = glm::translate(glm::mat4(1.0), glm::vec3(-radius / 15, radius * 1.25, radius * 0.75))
		* glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(1, 0, 0));;
	_eye2->setModelMat(auxMat);
	addEntity(_eye2);
}

void Droid::rollBall(GLfloat factor) {
	glm::mat4 auxMat = glm::rotate(_ball->modelMat(), glm::radians(factor), glm::vec3(1, 0, 0));
	_ball->setModelMat(auxMat);
}