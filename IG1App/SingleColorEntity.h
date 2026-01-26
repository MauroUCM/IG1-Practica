#include "Entity.h"

#pragma once
class SingleColorEntity : public Abs_Entity
{
private:
	glm::vec4 mColor;

public:
	SingleColorEntity(glm::vec4 color = (glm::vec4) 1);

	// Getter y setter de mColor	
	glm::vec4 GetColor() { return mColor; }
	void SetColor(glm::vec4 newColor) { mColor = newColor; }
	void render(const glm::mat4& modelViewMat) const override;
};

class RegularPolygon : public SingleColorEntity 
{
	RegularPolygon(GLuint num,  GLdouble r);
};

