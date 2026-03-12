#include "BoxOutline.h"


BoxOutline::BoxOutline(GLdouble length, Texture* mTexture) : EntityWithTexture(mTexture) {
	mMesh = Mesh::generateBoxOutline(100.0);

}