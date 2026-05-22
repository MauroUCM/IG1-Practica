#include "Disk.h"
#include "IndexMesh.h"
#include <numbers>

Disk::Disk(GLdouble h, GLdouble r, GLuint nRings, GLuint nSamples) {
	mMesh = IndexMesh::generateCone(h, r, r, nRings, nSamples);

}
