#include "Star3D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Star3D::Star3D(GLdouble re, GLuint np, GLdouble h) {
	mMesh = Mesh::generateStar3D(re, np, h);
}

void Star3D::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();
		
		// estrella inversa
		aMat = glm::scale(aMat, glm::vec3(-1.0f, -1.0f, -1.0f));
		upload(aMat);
		mMesh->render();
	}
}

void Star3D::update() {
	mModelMat = glm::rotate(mModelMat, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));	// eje horizontal
	mModelMat = glm::rotate(mModelMat, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));	// eje vertical
}