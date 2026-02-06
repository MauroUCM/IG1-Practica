#include "RGBTriangle.h"

RGBTriangle::RGBTriangle(GLuint r) {
	mMesh = Mesh::generateTriangle(r);

	std::vector<glm::vec4> col;
	col.emplace_back(1.0, 0.0, 0.0, 1.0);	// Red
	col.emplace_back(0.0, 1.0, 0.0, 1.0);	// Green
	col.emplace_back(0.0, 0.0, 1.0, 1.0);	// Blue
	mMesh->setColors(col);

}