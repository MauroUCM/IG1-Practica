#include "Torus.h"
#include "IndexMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <numbers>

Torus::Torus(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples) {

	double t = -std::numbers::pi;
	std::vector<glm::vec2> perfil(nPoints);

	for (int i = 0; i < nPoints; i++) {
		perfil[i] = { r*cos(t) + R, r*sin(t) + R };
		t = t + 2*(std::numbers::pi / nPoints);
	}

	mMesh = Mesh::generateByRevolution(perfil, nSamples);
	mMesh->setAllColors({ 0.0, 1.0, 0.0, 1.0 });
}

Torus::~Torus() {

}