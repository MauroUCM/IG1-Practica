#pragma once
#include "Mesh.h"
#include <numbers>

class IndexMesh : public Mesh
{
public:
	void load() override;
	void unload() override;
	void draw() const override;

	static IndexMesh* generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax = 2 * std::numbers::pi);
	static IndexMesh* generateIndexedBox8(GLdouble l);
	static IndexMesh* generateIndexedBox(GLdouble l);

	void buildNormalVectors();

protected:

private:
	std::vector<GLuint> vIndexes;
	GLuint mIBO;
};

