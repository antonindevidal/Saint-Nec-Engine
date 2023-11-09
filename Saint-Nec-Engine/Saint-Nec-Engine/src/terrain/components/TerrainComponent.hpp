#pragma once
#include <string>
#include <vector>
#include <stb_image.h>
#include <architecture/Component.hpp>
#include <architecture/SceneManager.hpp>
#include <graphics/Shader.hpp>


/**
 * Component that draw a terrain from a heightmap.
 */
class TerrainComponent :public sne::Component
{
public:

	/**
	 * Constructor.
	 * 
	 * @param heightmapPath Path for the image file.
	 * @param width Width of the terrain.
	 * @param height Height of the terrain.
	 * @param density Number of vertices per unite.
	 */
	TerrainComponent::TerrainComponent(const char* heightmapPath, const char* vertexShaderPath, const char* fragmentShaderPath, const unsigned int& terrainWidth, const unsigned int& terrainDepth, const unsigned int& density);
	~TerrainComponent();

	void update() override;
	void draw() const override;

private:
	unsigned int terrainWidth;
	unsigned int terrainDepth;
	std::vector<float> vertices;
	std::vector<int> indices;
	unsigned int heightmapID;

	/**
	* Vertex Buffer Object.
	*/
	unsigned int VBO;

	/**
	* Vertex Array Object.
	*/
	unsigned int VAO;

	/**
	* Element Buffer Object.
	*/
	unsigned int EBO;

	/**
	* Shader used to draw the terrain.
	*/
	sne::graphics::Shader shader;
};
