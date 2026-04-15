#include "Photo.h"
#include <glm/gtc/matrix_transform.hpp>

Photo::Photo() {
	mMesh = Mesh::generateRectangleTexCor(200, 200, 4, 4);

	mModelMat = glm::rotate(mModelMat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mModelMat = glm::translate(mModelMat, glm::vec3(1.0, 0.0, 0.0));
}

Photo::~Photo() {

}

void Photo::update() {

}