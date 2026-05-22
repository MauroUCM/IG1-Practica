#pragma once
#include "EntityWithTexture.h"

class SphereWithTexture : public EntityWithTexture
{
public:
	SphereWithTexture(GLdouble radius, GLuint nParallels, GLuint nMeridians, Texture* text);
	~SphereWithTexture() {};
};

