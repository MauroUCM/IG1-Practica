#pragma once
#include "Entity.h"
#include "Texture.h"

class EntityWithTexture : public Abs_Entity
{
public:
	EntityWithTexture(Texture* mTexture = nullptr, bool mModulate = false);
	~EntityWithTexture();

	virtual void render(const glm::mat4& modelViewMat) const override;

protected:
	Texture* mTexture;
	bool mModulate;
};

