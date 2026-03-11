#include "BoxOutline.h"


BoxOutline::BoxOutline(GLdouble length) {
	mMesh = Mesh::generateBoxOutline(100.0);

}