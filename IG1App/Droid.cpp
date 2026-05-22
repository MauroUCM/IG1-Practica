#include "Droid.h"
#include "Texture.h"
#include "SphereWithTexture.h"
#include "Disk.h"
#include "Cone.h"
#include <glm/gtc/matrix_transform.hpp>

Droid::Droid(GLdouble radius) {
	// sphere
	Texture* baText = new Texture();
	baText->load("../assets/images/container.jpg");
	addEntity(new SphereWithTexture(radius, 20, 20, baText));

	// head
	auto* head = new Cone(radius/2, radius, radius/2, 10, 20);
	head->SetColor({ 1.0, 1.0, 0.0, 1.0 });
	glm::mat4 auxMat = glm::translate(glm::mat4(1.0), glm::vec3(0, radius, 0));
	head->setModelMat(auxMat);
	addEntity(head);

	// eyes
	auto* eye1 = new Disk(radius / 2, radius / 15, 10, 20);
	auxMat = glm::translate(glm::mat4(1.0), glm::vec3(radius / 15, radius * 1.25, radius * 0.75))
		* glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(1, 0, 0));;
	eye1->setModelMat(auxMat);
	addEntity(eye1);

	auto* eye2 = new Disk(radius / 2, radius / 15, 10, 20);
	auxMat = glm::translate(glm::mat4(1.0), glm::vec3(-radius / 15, radius * 1.25, radius * 0.75))
		* glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(1, 0, 0));;
	eye2->setModelMat(auxMat);
	addEntity(eye2);
}