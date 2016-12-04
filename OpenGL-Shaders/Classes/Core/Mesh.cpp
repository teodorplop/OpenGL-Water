#include "Mesh.h"
#include "..\Objects\ObjLoader.h"

Mesh::Mesh(std::vector<glm::vec4> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<unsigned int> indices) {
	Buffer* vBuffer = new Buffer(vertices);
	Buffer* uvBuffer = new Buffer(uvs);
	Buffer* nBuffer = new Buffer(normals);

	vArray = new VertexArray();
	vArray->AddBuffer(vBuffer, 0);
	vArray->AddBuffer(uvBuffer, 1);
	vArray->AddBuffer(nBuffer, 2);

	iBuffer = new IndexBuffer(indices);
}
Mesh::~Mesh() {
	delete vArray;
	delete iBuffer;
}

VertexArray* Mesh::GetVertexArray() {
	return vArray;
}
IndexBuffer* Mesh::GetIndexBuffer() {
	return iBuffer;
}

Mesh* Mesh::LoadFromObj(const char* filename) {
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
	ObjLoader::LoadObj(filename, vertices, uvs, normals, indices);

	return new Mesh(vertices, uvs, normals, indices);
}