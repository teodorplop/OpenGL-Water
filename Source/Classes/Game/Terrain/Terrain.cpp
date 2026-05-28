#include "Terrain.h"
#include <vector>

// total square size
float Terrain::size = 1024.0f;
float Terrain::maxHeight = 100.0f;
const float Terrain::maxPixelColor = 256.0f * 256.0f * 256.0f;
int Terrain::cells = 256;
float** Terrain::heights = NULL;

Mesh* Terrain::GenerateMesh(const char* heightMap) {
	cells = 256;

	FIBITMAP* data = ImageUtils::Load_Image(heightMap);
	if (data == NULL) {
		fprintf(stderr, "Could not load height map: %s\n", heightMap);
	} else {
		cells = FreeImage_GetWidth(data);
		if (cells != FreeImage_GetHeight(data)) {
			fprintf(stderr, "Height map needs to be a square texture: %s\n", heightMap);
		}
	}
	heights = new float*[cells];
	for (int i = 0; i < cells; ++i) {
		heights[i] = new float[cells];
	}
	CalculateHeights(data);
	ImageUtils::Unload_Image(data);

	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	float cell = size / ((float)cells - 1);
	glm::vec2 position(0.0f, 0.0f);
	for (int i = 0; i < cells; ++i) {
		for (int j = 0; j < cells; ++j) {
			glm::vec4 vertex(position.x, heights[i][j], position.y, 1);
			glm::vec2 uv(position.x / size, position.y / size);
			glm::vec3 normal = CalculateNormal(i, j);

			vertices.push_back(vertex);
			uvs.push_back(uv);
			normals.push_back(normal);

			position.x += cell;
		}
		position.x = 0.0f;
		position.y += cell;
	}
	
	for (int i = 0; i < cells - 1; ++i) {
		for (int j = 0; j < cells - 1; ++j) {
			int bottomLeft = i * cells + j;
			int bottomRight = bottomLeft + 1;
			int topLeft = bottomLeft + cells;
			int topRight = topLeft + 1;

			indices.push_back(bottomLeft);
			indices.push_back(topRight);
			indices.push_back(bottomRight);

			indices.push_back(bottomLeft);
			indices.push_back(topLeft);
			indices.push_back(topRight);
		}
	}

	// Smoothing normals out
	for (int i = 1; i < cells - 1; ++i) {
		for (int j = 1; j < cells - 1; ++j) {
			int cell = i * cells + j;
			int bottom = cell - cells;
			int top = cell + cells;
			int left = cell - 1;
			int right = cell + 1;

			int bottomLeft = bottom - 1;
			int bottomRight = bottom + 1;
			int topLeft = top - 1;
			int topRight = top + 1;

			normals[cell] =
				glm::normalize((normals[bottom] + normals[top] + normals[left] + normals[right]
					+ normals[bottomLeft] + normals[bottomRight] + normals[topLeft] + normals[topRight]));
		}
	}

	for (int i = 0; i < cells; ++i) {
		delete[] heights[i];
	}
	delete[] heights;

	return new Mesh(vertices, uvs, normals, indices);
}

void Terrain::CalculateHeights(FIBITMAP* data) {
	for (int i = 0; i < cells; ++i) {
		for (int j = 0; j < cells; ++j) {
			heights[i][j] = data ? GetHeight(data, i, j) : 0.0f;
		}
	}

	// Smooth interpolation between heights so it does not look too edgy
	SmoothHeights(0.75f);
}
void Terrain::SmoothHeights(float alpha) {
	for (int i = 1; i < cells; ++i) {
		for (int j = 0; j < cells; ++j) {
			heights[i][j] = heights[i - 1][j] * (1.0f - alpha) + heights[i][j] * alpha;
		}
	}
	for (int i = cells - 2; i >= 0; --i) {
		for (int j = 0; j < cells; ++j) {
			heights[i][j] = heights[i + 1][j] * (1.0f - alpha) + heights[i][j] * alpha;
		}
	}
	for (int i = 0; i < cells; ++i) {
		for (int j = 1; j < cells; ++j) {
			heights[i][j] = heights[i][j - 1] * (1.0f - alpha) + heights[i][j] * alpha;
		}
	}
	for (int i = 0; i < cells; ++i) {
		for (int j = cells - 2; j >= 0; --j) {
			heights[i][j] = heights[i][j + 1] * (1.0f - alpha) + heights[i][j] * alpha;
		}
	}
}

glm::vec3 Terrain::CalculateNormal(const int& x, const int &y) {
	float heightLeft = x > 0 ? heights[x - 1][y] : 0.0f;
	float heightRight = x < cells - 1 ? heights[x + 1][y] : 0.0f;
	float heightUp = y < cells - 1 ? heights[x][y + 1] : 0.0f;
	float heightDown = y > 0 ? heights[x][y - 1] : 0.0f;

	return glm::normalize(glm::vec3(heightLeft - heightRight, 2.0f, heightDown - heightUp));
}

float Terrain::GetHeight(FIBITMAP* data, const int& x, const int& y) {
	RGBQUAD rgbQuad;
	if (!FreeImage_GetPixelColor(data, x, y, &rgbQuad)) {
		fprintf(stderr, "Failed to get pixel color\n");
		return 0.0f;
	}

	float pixelColor = (float)rgbQuad.rgbRed * (1 << 16) + rgbQuad.rgbGreen * (1 << 8) + rgbQuad.rgbBlue;

	pixelColor -= maxPixelColor / 2.0f;
	pixelColor /= maxPixelColor / 2.0f;

	return pixelColor * maxHeight;
}

/*float GetYCoord(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const float& x, const float& z) {
	glm::vec3 p1p2 = p2 - p1, p1p3 = p3 - p1;
	glm::vec3 p1p2Xp1p3 = glm::cross(p1p2, p1p3);
	float a = p1p2Xp1p3.x, b = p1p2Xp1p3.y, c = p1p2Xp1p3.z;
	float d = -(a * p1.x + b * p1.y + c * p1.z);

	return -(a * x + c * z + d) / b;
}

float Terrain::GetHeight(const float& worldX, const float& worldZ) {
	float cellSize = size / ((float)cells - 1);

	int gridI = (int)(worldZ / cellSize), gridJ = (int)(worldX / cellSize);
	if (gridI < 0 || gridI >= cells - 1 || gridJ < 0 || gridJ >= cells - 1) {
		return 0.0f;
	}

	float xCoord = fmod(worldX, cellSize) / cellSize, zCoord = fmod(worldZ, cellSize) / cellSize;
	float answer = 0.0f;

	if (xCoord < zCoord) {
		answer = GetYCoord(
			glm::vec3(0.0f, heights[gridI][gridJ], 0.0f),
			glm::vec3(1.0f, heights[gridI + 1][gridJ + 1], 1.0f),
			glm::vec3(0.0f, heights[gridI + 1][gridJ], 1.0f),
			xCoord, zCoord
			);
	}
	else {
		answer = GetYCoord(
			glm::vec3(0.0f, heights[gridI][gridJ], 0.0f),
			glm::vec3(1.0f, heights[gridI][gridJ + 1], 0.0f),
			glm::vec3(1.0f, heights[gridI + 1][gridJ + 1], 1.0f),
			xCoord, zCoord
			);
	}

	return answer;
}*/