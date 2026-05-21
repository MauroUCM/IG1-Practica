#include "SingleColorEntity.h"

SingleColorEntity::SingleColorEntity(glm::vec4 color) : mColor(color)
{
	mShader = Shader::get("vcolors");
}

void SingleColorEntity::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use(); 
		mShader->setUniform("color", mColor);
		upload(aMat);
		mMesh->render();
	}
}