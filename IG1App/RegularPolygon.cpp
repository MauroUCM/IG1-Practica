#include "RegularPolygon.h"
#include "Mesh.h"

RegularPolygon::RegularPolygon(GLuint num, GLdouble r)
{
	mMesh = Mesh::generateRegularPolygon(num, r);
	mMesh->colorAllV(GetColor());
}

RegularPolygon::RegularPolygon(GLuint num, GLdouble r, glm::vec4 color) : SingleColorEntity(color)
{
	mMesh = Mesh::generateRegularPolygon(num, r);
	mMesh->colorAllV(GetColor());

}