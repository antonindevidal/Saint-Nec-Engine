#pragma once
#include <string>
#include <architecture/Component.hpp>
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
	TerrainComponent(const std::string& heightmapPath, const unsigned int& width, const unsigned int& depth, const unsigned int& density);
	~TerrainComponent();

	void update() const override;
	void draw() const override;

private:
	unsigned long heightmapID;
};
