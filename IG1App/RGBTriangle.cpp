#include "RGBTriangle.h"
#include <glm/gtc/matrix_transform.hpp>

RGBTriangle::RGBTriangle(GLuint r, float rotDir) : rotDir(rotDir) {
	mMesh = Mesh::generateTriangle(r);

	std::vector<glm::vec4> col;
	col.emplace_back(1.0, 0.0, 0.0, 1.0);	// Red
	col.emplace_back(0.0, 1.0, 0.0, 1.0);	// Green
	col.emplace_back(0.0, 0.0, 1.0, 1.0);	// Blue
	mMesh->setColors(col);

}

void RGBTriangle::update() {
	mModelMat = glm::rotate(mModelMat, glm::radians(2.0f * rotDir), glm::vec3(0.0f, 0.0f, 1.0f));
}