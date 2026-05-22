#include "IndexedBox.h"
#include "IndexMesh.h"
#include <glm/gtc/matrix_transform.hpp>

IndexedBox::IndexedBox(GLdouble l) : ColorMaterialEntity()
{
	mMesh = IndexMesh::generateIndexedBox8(l);

}