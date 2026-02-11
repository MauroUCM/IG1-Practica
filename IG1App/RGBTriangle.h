#include "Entity.h"

#pragma once
class RGBTriangle : public EntityWithColors
{
public:

	RGBTriangle(GLuint r, float rotDir = 1);
	~RGBTriangle() {};

	void update() override;

private:
	float rotDir;
};

