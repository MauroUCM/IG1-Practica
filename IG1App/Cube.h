#include "Entity.h"

#pragma once
class Cube : public EntityWithColors
{
public:
	Cube(GLdouble l);
	~Cube() {};

	virtual void render(const glm::mat4& modelViewMat) const override;
	int iState = 0;
	int state = 0;
	void update() override;

};

