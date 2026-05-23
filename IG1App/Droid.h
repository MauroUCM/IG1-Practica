#pragma once
#include "CompoundEntity.h"
#include "SphereWithTexture.h"
#include "Disk.h"
#include "Cone.h"

class Droid : public CompoundEntity
{
public:
	Droid(GLdouble radius);
	~Droid() {};

	void rollBall(GLfloat);

private:
	SphereWithTexture* _ball;
	Cone* _head;
	Disk* _eye1, *_eye2;
};

