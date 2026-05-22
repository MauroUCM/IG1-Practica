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
	static IndexMesh* generateSphere(GLdouble radius, GLuint nParallels, GLuint nMeridians);
	static IndexMesh* generateCone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples);

	void buildNormalVectors();

protected:

private:
	std::vector<GLuint> vIndexes;
	GLuint mIBO;
};

