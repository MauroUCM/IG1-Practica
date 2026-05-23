#pragma once
#include "Entity.h"
#include "Material.h"

class EntityWithMaterial : public Abs_Entity
{
public:
	EntityWithMaterial(Material material);
	~EntityWithMaterial() {};

	void render(const glm::mat4& modelViewMat) const override;

	// getters y setters
	Material* getMaterial() { return &mMaterial; }
	void setMaterial(Material material) { mMaterial = material; }
	static void toggleShowNormals() { mShowNormals = !mShowNormals; };

private:
	Material mMaterial;
	static bool mShowNormals;

};

