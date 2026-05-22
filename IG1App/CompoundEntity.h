#pragma once
#include "Entity.h"
#include <vector>

class CompoundEntity : public Abs_Entity
{
public:
	CompoundEntity();
	~CompoundEntity();

	virtual void render(const glm::mat4& modelViewMat) const override;

	void update() override;
	void load() override;
	void unload() override;

	void addEntity(Abs_Entity* ae);


protected:
	std::vector<Abs_Entity*> gObjects;

};

