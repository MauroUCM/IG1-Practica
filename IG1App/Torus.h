#pragma once
#include "SingleColorEntity.h"

class Torus : public SingleColorEntity
{
public:
	Torus(GLdouble R, GLdouble r, GLuint nPoints = 40, GLuint nSamples = 40);
	~Torus();

};
