#pragma once
#include "SingleColorEntity.h"

class ColorMaterialEntity : public SingleColorEntity
{
public:
	ColorMaterialEntity();
	~ColorMaterialEntity() {};

	void render(const glm::mat4& modelViewMat) const override;
	static void toggleShowNormals() { mShowNormals = !mShowNormals; };
private:
	static bool mShowNormals;
};

