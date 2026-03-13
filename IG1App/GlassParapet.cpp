#include "GlassParapet.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GlassParapet::GlassParapet(GLdouble length, Texture* mTexture) : EntityWithTexture(mTexture) {
	mMesh = Mesh::generateBoxOutline(length);
	mModelMat = glm::scale(mModelMat, glm::vec3(1.0f, 0.25f, 1.0f));

	mModelMat = glm::translate(mModelMat, glm::vec3(-length/2, -length / 2, -length/2));
}

void GlassParapet::render(const glm::mat4& modelViewMat) const {
	glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
	mShader->use();
	mShader->setUniform("modulate", mModulate);
	upload(aMat);
	if (mTexture != nullptr) mTexture->bind();
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	mMesh->render();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	if (mTexture != nullptr) mTexture->unbind();



}