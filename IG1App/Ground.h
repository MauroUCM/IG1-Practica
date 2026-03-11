#pragma once
#include "EntityWithTexture.h"

class Ground : public EntityWithTexture
{
public:
	Ground(Texture* mTexture = nullptr);
	~Ground();

};

