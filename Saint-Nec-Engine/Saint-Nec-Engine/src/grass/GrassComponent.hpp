#pragma once
#include <graphics/GraphicComponent.hpp>

class GrassComponent : public sne::graphics::GraphicComponent
{
public:
	GrassComponent(const int& width, const int& depth, const int nbInstances, const char* vertexShaderPath, const char* fragmentShaderPath);
	void draw() const override;
	void update() override;
private:
	unsigned int instanceVBO;
	int nbInstances;

	float testDir;
	glm::vec3 topGrassColor;
	glm::vec3 bottomGrassColor;
};
