#pragma once
#include <architecture/SceneManager.hpp>
#include <graphics/GraphicComponent.hpp>

class TessellationTerrain: public sne::graphics::GraphicComponent
{
public:
	TessellationTerrain(const unsigned int& width, const unsigned int& depth, const unsigned int& density, const char* vertexShaderPath, const char* fragmentShaderPath, const char* tessellationControlPath, const char* tessellationEvaluationPath);

	void draw() const override;
private:
	unsigned int nbIndices;
};