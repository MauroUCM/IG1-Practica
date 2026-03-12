#pragma once
#include "EntityWithTexture.h"

class BoxOutline : public EntityWithTexture
{
public:
	BoxOutline(GLdouble length, Texture* mTexture = nullptr);
	~BoxOutline() {};

};

