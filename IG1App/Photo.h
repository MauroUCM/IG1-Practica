#pragma once
#include "EntityWithTexture.h"

class Photo : public EntityWithTexture
{
	Photo();
	~Photo() {};

	virtual void update() override;
};

