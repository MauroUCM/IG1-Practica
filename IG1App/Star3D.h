#pragma once
#include "SingleColorEntity.h"

class Star3D : public SingleColorEntity
{
public:
	Star3D(GLdouble re, GLuint np, GLdouble h);
	~Star3D() {};

	virtual void render(const glm::mat4& modelViewMat) const override;
};

