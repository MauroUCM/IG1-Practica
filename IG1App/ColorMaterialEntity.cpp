#include "ColorMaterialEntity.h"

ColorMaterialEntity::ColorMaterialEntity() : SingleColorEntity({ 0.0, 1.0, 0.0, 1.0 }) {
	mShader = Shader::get("simple_light");
}