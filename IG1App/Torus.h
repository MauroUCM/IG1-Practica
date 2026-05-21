#pragma once
#include "SingleColorEntity.h"
#include "ColorMaterialEntity.h"

class Torus : public ColorMaterialEntity
{
public:
	Torus(GLdouble R, GLdouble r, GLuint nPoints = 40, GLuint nSamples = 40);
	~Torus();

};
