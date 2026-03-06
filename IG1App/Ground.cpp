#include "Ground.h"
#include <glm/gtc/matrix_transform.hpp>

Ground::Ground(Texture* mTexture) : EntityWithTexture(mTexture){
	mMesh = Mesh::generateRectangleTexCor(500, 500);

	mModelMat = glm::rotate(mModelMat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

Ground::~Ground() {

}