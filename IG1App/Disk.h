#pragma once
#include "ColorMaterialEntity.h"

class Disk : public ColorMaterialEntity
{
public:
	Disk(GLdouble h, GLdouble r, GLuint nRings, GLuint nSamples);
	~Disk() {};
};

