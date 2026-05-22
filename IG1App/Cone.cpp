#include "Cone.h"
#include "IndexMesh.h"
#include <numbers>

Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples) {
	mMesh = IndexMesh::generateCone(h, r, R, nRings, nSamples);
}