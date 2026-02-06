#include "SingleColorEntity.h"

#pragma once
class RegularPolygon : public SingleColorEntity
{
public:
	RegularPolygon(GLuint num, GLdouble r);
	RegularPolygon(GLuint num, GLdouble r, glm::vec4 color);
	~RegularPolygon() {};

};

