#include "Star3D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Star3D::Star3D(GLdouble re, GLuint np, GLdouble h, Texture* mTexture) : EntityWithTexture(mTexture) {
	mMesh = Mesh::generateStar3DTexCor(re, np, h);
}

void Star3D::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		upload(aMat);
		if (mTexture != nullptr) mTexture->bind();
		mMesh->render();
		
		// estrella inversa
		aMat = glm::scale(aMat, glm::vec3(-1.0f, -1.0f, -1.0f));
		upload(aMat);
		mMesh->render();
		if (mTexture != nullptr) mTexture->unbind();
	}
}
//hacer rotacion de esrellas guardando la matriz y haciendola por separado
void Star3D::update() {
	glm::mat4 auxMat = mModelMat;
	mModelMat = glm::rotate(mModelMat, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));	// eje horizontal
	mModelMat = glm::rotate(auxMat, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));	// eje vertical
}