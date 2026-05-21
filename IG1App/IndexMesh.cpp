	#include "IndexMesh.h"

using namespace std;	

void IndexMesh::load() {
	Mesh::load(); 
}

void IndexMesh::unload() {
	Mesh::unload();
}

void IndexMesh::draw() const {
	glDrawElements(
		mPrimitive, // primitiva ( GL_TRIANGLES , etc.)
		vIndexes.size(), // número de índices
		GL_UNSIGNED_INT, // tipo de los índices
		nullptr // offset en el VBO de índices
	);
}

IndexMesh* IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax)
{
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;
	int tamPerfil = profile.size();
	mesh->vVertices.reserve(nSamples * tamPerfil);

	// Genera los vértices de las muestras
	GLdouble theta1 = 2 * numbers::pi / nSamples;
	for (int i = 0; i <= nSamples; ++i) { // muestra i-ésima
		GLdouble c = cos(i * theta1), s = sin(i * theta1);
		for (auto p : profile) // rota el perfil
			mesh->vVertices.emplace_back(p.x * c, p.y, -p.x * s);
	}

	for (int i = 0; i < nSamples; ++i){ // caras i a i + 1
		for (int j = 0; j < tamPerfil - 1; ++j) { // una cara
			if (profile[j].x != 0.0) // triángulo inferior
				for (auto [s, t] : { pair{i, j}, {i, j + 1}, {i + 1, j} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
			if (profile[j + 1].x != 0.0) // triángulo superior
				for (auto [s, t] : { pair{i, j + 1}, {i + 1, j + 1}, {i + 1, j} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
		}
	}

	mesh->mNumVertices = mesh->vVertices.size();
	return mesh;
}

void IndexMesh::buildNormalVectors(IndexMesh* mesh)
{
	std::vector<GLuint>& indexes = mesh->vIndexes;
	glm::dvec3 normalVec = glm::dvec3(0.0, 0.0, 0.0);
	int numVer = indexes.size();
	
	for (int i = 0; i < numVer; i++)
	{
		glm::dvec3 verAct = mesh->vVertices[indexes[i]];
		glm::dvec3 verSig = mesh->vVertices[indexes[(i + 1) % numVer]];
		normalVec.x += (verAct.y - verSig.y) * (verAct.z + verSig.z);
		normalVec.y += (verAct.z - verSig.z) * (verAct.x + verSig.x);
		normalVec.z += (verAct.x - verSig.x) * (verAct.y + verSig.y);
	}

	// Normalizar la normal calculada
	normalVec = glm::normalize(normalVec);
	mesh->vNormals[indexes[0]] = normalVec;
}
