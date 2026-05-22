#pragma once
#include "SingleColorEntity.h"

class ColorMaterialEntity : public SingleColorEntity
{
public:
	ColorMaterialEntity(glm::vec4 color = { 0.0, 1.0, 0.0, 1.0 });
	~ColorMaterialEntity() {};

	void render(const glm::mat4& modelViewMat) const override;
	static void toggleShowNormals() { mShowNormals = !mShowNormals; };
private:
	static bool mShowNormals;
};

