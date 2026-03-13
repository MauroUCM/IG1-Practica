#pragma once
#include "EntityWithTexture.h"

class GlassParapet : public EntityWithTexture {
public:
	GlassParapet(GLdouble length, Texture* mTexture);
	~GlassParapet() {};

	virtual void render(const glm::mat4& modelViewMat) const override;
};

