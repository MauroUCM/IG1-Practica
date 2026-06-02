#pragma once
#include "SingleColorEntity.h"
#include "EntityWithMaterial.h"

class ColorMaterialEntity : public EntityWithMaterial
{
public:
	ColorMaterialEntity(glm::vec4 color = { 0.0, 1.0, 0.0, 1.0 });
	~ColorMaterialEntity() {};

	void SetColor(glm::vec4 color) { setMaterial(Material(color)); };
	//void render(const glm::mat4& modelViewMat) const override;
};

