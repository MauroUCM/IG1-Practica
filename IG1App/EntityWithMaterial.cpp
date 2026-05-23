#include "EntityWithMaterial.h"

EntityWithMaterial::EntityWithMaterial(Material material) : mMaterial(material) {
	mShader = Shader::get("light");
}

void EntityWithMaterial::render(const glm::mat4& modelViewMat) const
{
	mShader->use();
	// Carga los atributos del material en la GPU
	mMaterial.upload(*mShader);
	upload(modelViewMat * mModelMat);
	mMesh->render();

	if (mShowNormals) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		Shader::get("normals")->use();
		upload(aMat);
		mMesh->render();
	}
}