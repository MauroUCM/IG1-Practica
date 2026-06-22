#pragma once
#include "CompoundEntity.h"
#include "SphereWithTexture.h"
#include "Disk.h"
#include "Cone.h"
#include "Light.h"

class Droid : public CompoundEntity
{
public:
	Droid(GLdouble radius);
	~Droid() {};

	void rollBall(GLfloat);
	void toggleLight() { _spotLight->setEnabled(!_spotLight->enabled()); };
	SpotLight* getLight() { return _spotLight; }

private:
	SphereWithTexture* _ball;
	Cone* _head;
	Disk* _eye1, *_eye2;
	SpotLight* _spotLight;
};

