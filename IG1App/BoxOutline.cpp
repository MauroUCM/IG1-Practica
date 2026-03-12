#include "BoxOutline.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

BoxOutline::BoxOutline(GLdouble length, Texture* mTexture, Texture* inTexture) : EntityWithTexture(mTexture), inTexture(inTexture) {
	mMesh = Mesh::generateBoxOutline(100.0);
}

void BoxOutline::render(const glm::mat4& modelViewMat) const 
{
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", mModulate);
		upload(aMat);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		if (mTexture != nullptr) mTexture->bind();
		mMesh->render();
		if (mTexture != nullptr) mTexture->unbind();

		glCullFace(GL_FRONT);
		if (inTexture != nullptr) inTexture->bind();
		mMesh->render();
		if (inTexture != nullptr) inTexture->unbind();

		glDisable(GL_CULL_FACE);
	}

}