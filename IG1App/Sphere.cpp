#include "Sphere.h"
#include "IndexMesh.h"
#include <numbers>

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians) : ColorMaterialEntity()
{
	mMesh = IndexMesh::generateSphere(radius, nParallels, nMeridians);
}
