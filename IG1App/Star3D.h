#pragma once
#include "EntityWithTexture.h"

class Star3D : public EntityWithTexture
{
public:
	Star3D(GLdouble re, GLuint np, GLdouble h, Texture* mTexture);
	~Star3D() {};

	virtual void render(const glm::mat4& modelViewMat) const override;
	void update() override;

private:
	float _rot;
};

