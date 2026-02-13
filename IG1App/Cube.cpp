#include "Cube.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Cube::Cube(GLdouble l) {
	mMesh = Mesh::generateRGBCubeTriangles(l);
}

void Cube::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		upload(aMat);

		glEnable(GL_CULL_FACE);

		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		mMesh->render();

		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		glDisable(GL_CULL_FACE);
	}
}

void Cube::update() {
	if (iState == 270) {
		state++;
		iState = 0;
		if (state == 3) {
			state = 0;
		}
	}
	
	switch (state) {
	case 0:
		mModelMat = glm::rotate(mModelMat, glm::radians(-1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	case 1:
		mModelMat = glm::rotate(mModelMat, glm::radians(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		break;
	case 2:
		mModelMat = glm::rotate(mModelMat, glm::radians(-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		break;
	}
	iState++;
	

}