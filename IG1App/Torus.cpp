#include "Torus.h"
#include "IndexMesh.h"
#include <numbers>

Torus::Torus(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples) : ColorMaterialEntity() {
	double t = -std::numbers::pi;
	std::vector<glm::vec2> profile(nPoints + 1);

	for (int i = 0; i <= nPoints; i++) {
		profile[i] = { r*cos(t) + R, r*sin(t) };
		t = t + 2*(std::numbers::pi / nPoints);
	}

	mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}

Torus::~Torus() {

}