#include "ColorMaterialEntity.h"

bool ColorMaterialEntity::mShowNormals = false;

ColorMaterialEntity::ColorMaterialEntity() : SingleColorEntity({ 0.0, 1.0, 0.0, 1.0 }) 
{
	mShader = Shader::get("simple_light");
}

void ColorMaterialEntity::render(const glm::mat4& modelViewMat) const 
{
	SingleColorEntity::render(modelViewMat);
	if (mShowNormals) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		Shader::get("normals")->use();
		upload(aMat);
		mMesh->render();
	}
}