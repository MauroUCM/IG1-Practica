#include "EntityWithTexture.h"

using namespace glm;

EntityWithTexture::EntityWithTexture(bool modul, Texture* text) : mTexture(text), mModulate(modul) {
	mShader = Shader::get("texture");
}	

EntityWithTexture::~EntityWithTexture() {

}

void
EntityWithTexture::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", mModulate);
		upload(aMat);
		if(mTexture != nullptr) mTexture->bind();
		mMesh->render();
		if(mTexture!= nullptr) mTexture->unbind();
	}
}