	#include "IndexMesh.h"

using namespace std;	
using namespace glm;

void IndexMesh::load() {
	Mesh::load(); 
	glBindVertexArray(mVAO);
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		vIndexes.size() * sizeof(GLuint),
		vIndexes.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
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

void IndexMesh::buildNormalVectors()
{
	vNormals.clear();
	vNormals.resize(vVertices.size(), vec3(0.0f));

	//Cálculo de normales
	for (int i = 0; i < vIndexes.size(); i += 3) {
		GLuint i0 = vIndexes[i];
		GLuint i1 = vIndexes[i + 1];
		GLuint i2 = vIndexes[i + 2];

		vec3 n = normalize(cross(vVertices[i1] - vVertices[i0], vVertices[i2] - vVertices[i0]));
		vNormals[i0] += n;
		vNormals[i1] += n;
		vNormals[i2] += n;
	}

	for (auto& n : vNormals) n = normalize(n);
}

IndexMesh* IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax)
{
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;

	int tamPerfil = profile.size();
	mesh->vVertices.reserve(nSamples * tamPerfil);
	mesh->vTexCoords.reserve(nSamples * tamPerfil);

	// Genera los v�rtices de las muestras
	GLdouble theta1 = angleMax / nSamples;
	for (int i = 0; i <= nSamples; ++i) { // muestra i-�sima
		GLdouble c = cos(i * theta1), s = sin(i * theta1);
		for (int j = 0; j < profile.size(); j++) {
			mesh->vVertices.emplace_back(profile[j].x * c, profile[j].y, -profile[j].x * s);

			GLfloat u = (GLfloat)i / nSamples;
			GLfloat v = (GLfloat)j / tamPerfil;
			mesh->vTexCoords.emplace_back(u, v);
		}
	}
	for (int i = 0; i < nSamples; ++i) { // caras i a i + 1
		GLuint nextI = (i + 1) % nSamples;
		for (int j = 0; j < tamPerfil - 1; ++j) { // una cara
			if (profile[j].x != 0.0) // tri�ngulo inferior
				for (auto [s, t] : { pair{i, j}, {nextI, j}, { i, j + 1 } })
					mesh->vIndexes.push_back(s * tamPerfil + t);
			if (profile[j + 1].x != 0.0) // tri�ngulo superior
				for (auto [s, t] : { pair{i, j + 1}, {nextI, j}, {nextI, j + 1} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
		}
	}
	mesh->mNumVertices = mesh->vVertices.size();
	mesh->buildNormalVectors();
	return mesh;
}

IndexMesh* IndexMesh::generateIndexedBox8(GLdouble l) 
{
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;

	// vertexes
	mesh->vVertices.reserve(8);
	mesh->mNumVertices = 8;
	mesh->vVertices.emplace_back(l, l, 0);
	mesh->vVertices.emplace_back(l, 0, 0);
	mesh->vVertices.emplace_back(l, l, l);
	mesh->vVertices.emplace_back(l, 0, l);
	mesh->vVertices.emplace_back(0, l, l);
	mesh->vVertices.emplace_back(0, 0, l);
	mesh->vVertices.emplace_back(0, l, 0);
	mesh->vVertices.emplace_back(0, 0, 0);

	// indexes
	mesh->vIndexes.reserve(36);
	mesh->vIndexes = {
		2, 1, 0, 3, 1, 2,
		4, 3, 2, 5, 3, 4,
		6, 5, 4, 7, 5, 6,
		0, 7, 6, 1, 7, 0,
		2, 6, 4, 0, 6, 2,
		3, 7, 1, 5, 7, 3
	};

	mesh->buildNormalVectors();
	return mesh;
}

IndexMesh* IndexMesh::generateIndexedBox(GLdouble l)
{
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;

	// Vertexes
	mesh->vVertices.reserve(24);
	mesh->mNumVertices = 24;

	// Back face
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	mesh->vVertices.emplace_back(l, l, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);

	// Front face
	mesh->vVertices.emplace_back(l, l, l);
	mesh->vVertices.emplace_back(0.0, l, l);
	mesh->vVertices.emplace_back(0.0, 0.0, l);
	mesh->vVertices.emplace_back(l, 0.0, l);

	// Left face
	mesh->vVertices.emplace_back(0.0, l, l);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	// Right face
	mesh->vVertices.emplace_back(l, l, 0.0);
	mesh->vVertices.emplace_back(l, l, l);
	mesh->vVertices.emplace_back(l, 0.0, l);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);

	// Top face
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	mesh->vVertices.emplace_back(0.0, l, l);
	mesh->vVertices.emplace_back(l, l, l);
	mesh->vVertices.emplace_back(l, l, 0.0);

	// Bottom face
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);
	mesh->vVertices.emplace_back(l, 0.0, l);

	// Indexes	
	mesh->vIndexes.reserve(36);
	mesh->vIndexes = {
		0, 1, 2, 1, 3, 2,	//
		4, 5, 6, 4, 6, 7,	//
		8, 9, 10, 10, 11, 8,	//
		12, 13, 14, 12, 14, 15,	//
		16, 17, 18, 19, 16, 18,	//
		20, 21, 22, 21, 23, 22	//
	};

	mesh->buildNormalVectors();
	return mesh;
}

IndexMesh* IndexMesh::generateSphere(GLdouble radius, GLuint nParallels, GLuint nMeridians) {
	IndexMesh* mesh = new IndexMesh;
	double t = 3 * (std::numbers::pi / 2);
	std::vector<glm::vec2> profile;

	for (int i = 0; i < nParallels; i++) {
		profile.emplace_back(radius * cos(t), radius * sin(t) );
		t = t - std::numbers::pi / nParallels;
	}
	profile.emplace_back(radius * cos(t), radius * sin(t));

	mesh = IndexMesh::generateByRevolution(profile, nMeridians);
	mesh->buildNormalVectors();
	return mesh;
}

IndexMesh* IndexMesh::generateCone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples) {
	IndexMesh* mesh = new IndexMesh;
	std::vector<glm::vec2> profile;

	profile.emplace_back(0, 0);
	for (int i = 0; i <= nRings; i++) {
		profile.emplace_back(r + (R - r) * i /nRings, h * i /nRings);
	}
	profile.emplace_back(0, h);

	mesh = IndexMesh::generateByRevolution(profile, nSamples);
	mesh->buildNormalVectors();
	return mesh;
}
