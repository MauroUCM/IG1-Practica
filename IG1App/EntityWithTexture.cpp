#include "EntityWithTexture.h"
#include <iostream>

EntityWithTexture::EntityWithTexture(Texture* text, bool modul) : mTexture(text), mModulate(modul) {
	mShader = Shader::get("texture");
}	

EntityWithTexture::~EntityWithTexture() {

}

void
EntityWithTexture::render(glm::mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", mModulate);
		upload(aMat);
		if(mTexture != nullptr) mTexture->bind();
		mMesh->render();
		if(mTexture!= nullptr) mTexture->unbind();
	}
}