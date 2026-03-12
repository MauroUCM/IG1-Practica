#pragma once
#include "EntityWithTexture.h"

class BoxOutline : public EntityWithTexture
{
public:
	BoxOutline(GLdouble length, Texture* mTexture, Texture* inTexture);
	~BoxOutline() {};

	virtual void render(const glm::mat4& modelViewMat) const override;

private:
	Texture* inTexture;
};

