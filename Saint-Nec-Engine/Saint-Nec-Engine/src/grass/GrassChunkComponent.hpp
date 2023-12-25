#pragma once
#include <graphics/GraphicComponent.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <architecture/Scene.hpp>
#include <imgui.h>

class GrassChunkComponent : public sne::graphics::GraphicComponent
{
public:
	GrassChunkComponent(const int& width, const int& chunkSize, const int nbInstancesPerChunk, const char* vertexShaderPath, const char* fragmentShaderPath);
	void draw() const override;
	void update() override;

	void genLOD1(const int& chunkSize, const std::vector<float>& positions);
	void genLOD2(const int& chunkSize, const std::vector<float>& positions);

private:
	unsigned int instanceVBO;
	int nbInstancesPerChunk;
	int chunkSize;
	std::vector<glm::vec3> chunkPositions;

	unsigned int VBO2;
	unsigned int VAO2;
	unsigned int EBO2;
	unsigned int instanceVBO2;
	unsigned int renderedElementCount2;

	static const float LODTreshold;

	float testDir;

	glm::vec3 bottomGrassColor;
	glm::vec3 topGrassColor;

	bool isChunkInsideFrustum( const glm::vec3& chunkPosition) const;
};
