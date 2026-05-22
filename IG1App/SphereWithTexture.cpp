#include "SphereWithTexture.h"
#include "IndexMesh.h"

SphereWithTexture::SphereWithTexture(GLdouble radius, GLuint nParallels, GLuint nMeridians, Texture* text) 
	: EntityWithTexture(text) {
	mMesh = IndexMesh::generateSphere(radius, nParallels, nMeridians);
}
