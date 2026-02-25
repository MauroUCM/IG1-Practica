#pragma once
#include "Entity.h"
#include "Texture.h"

class EntityWithTexture : public Abs_Entity
{
public:
	EntityWithTexture(Texture* mTexture, bool mModulate);
	~EntityWithTexture();


protected:
	Texture* mTexture;
	bool mModulate;
};

