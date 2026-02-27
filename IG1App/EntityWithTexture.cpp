#include "EntityWithTexture.h"

using namespace glm;

EntityWithTexture::EntityWithTexture(Texture* text, bool modul) : mTexture(text), mModulate(modul) {
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
		mTexture->bind();
		mMesh->render();
		mTexture->unbind();
	}
}