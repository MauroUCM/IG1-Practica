#include "Entity.h"

#pragma once
class RGBRectangle : public EntityWithColors
{
public:
	RGBRectangle(GLdouble w, GLdouble h);
	~RGBRectangle() {};

	virtual void render(const glm::mat4& modelViewMat) const override;
};
