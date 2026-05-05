#include "IndexMesh.h"
//#include <vector>

using namespace std;	



IndexMesh* IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples,
	GLfloat angleMax = 2 * std::numbers::pi) 
	{
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;

	// Genera los vértices de las muestras
	vector<vector<glm::vec3>> vs(nSamples + 1);
	GLdouble theta1 = 2 * numbers::pi / nSamples;

	for (int i = 0; i <= nSamples; ++i) { // muestra i-ésima
		GLdouble c = cos(i * theta1), s = sin(i * theta1);
		vs[i].reserve(profile.size());
		for (auto p : profile) // rota el perfil
			vs[i].emplace_back(p.x * c, p.y, -p.x * s);
	}

	for (int i = 0; i < nSamples; ++i) // caras i a i + 1
		for (int j = 0; j < profile.size() - 1; ++j) { // una cara
			// Triángulo inferior (si no es degenerado)
			if (profile[j].x != 0.0) {
				mesh->vVertices.push_back(vs[i][j]);
				mesh->vVertices.push_back(vs[i][j + 1]);
				mesh->vVertices.push_back(vs[i + 1][j]);
			}
			// Triángulo superior (si no es degenerado)
			if (profile[j + 1].x != 0.0) {
				for (auto [s, t] : { pair{i, j + 1}, {i + 1, j + 1}, {i + 1, j} })
					mesh->vVertices.push_back(vs[s][t]); // más corto
			}
		}

	mesh->mNumVertices = mesh->vVertices.size();
	return mesh;
}
