#pragma once
/**
 * @file GrassChunkComponent.hpp
 * @brief Manage grass field with instancing, chunk, frustum cullin and LOD.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date january 14th 2024.
 *
 */

#include <vector>
#include <glm/glm.hpp>
#include <graphics/GraphicComponent.hpp>
#include <architecture/Scene.hpp>

/**
*	@class GrassChunkComponent.
*	@brief Manage grass field with chunk frustum cullin and 2 meshes LOD.
*/
class GrassChunkComponent : public sne::graphics::GraphicComponent
{
public:
	/**
	 * Constructor for GrassChunkComponent.
	 */
	GrassChunkComponent(const int& width, const int& chunkSize, const int nbInstancesPerChunk, const char* vertexShaderPath, const char* fragmentShaderPath);
	
	/**
	* Draw function.
	* No logic should happen there.
	*/
	void draw() const override;

	/**
	* Update function.
	* All the logic happens here.
	*/
	void update() override;

	/**
	 * @brief Generates first LOD geometry.
	 * 
	 * @param positions Positions for all baldes in a chunk.
	 */
	void genLOD1(const std::vector<float>& positions);

	/**
	 * @brief Generates second LOD geometry.
	 * 
	 * @param positions Positions for all baldes in a chunk.
	 */
	void genLOD2(const std::vector<float>& positions);

private:
	/**
	 * @brief Instance VBO for first LOD geometry.
	 */
	unsigned int instanceVBO;
	
	/**
	 * @brief VBO for LOD level 2.
	 */
	unsigned int VBO2;

	/**
	 * @brief VAO for LOD level 2.
	 */
	unsigned int VAO2;

	/**
	 * @brief EBO for LOD level 2.
	 */
	unsigned int EBO2;

	/**
	 * @brief Instance VBO for LOD level 2.
	 */
	unsigned int instanceVBO2;

	/**
	 * Number of points for LOD 2.
	 */
	unsigned int renderedElementCount2;

	/**
	 * @brief Number of grass blades per chunk.
	 */
	int nbInstancesPerChunk;

	/**
	 * @brief Size of a chunk (square).
	 */
	int chunkSize;
	
	/**
	 * @brief List of chunks positions.
	 */
	std::vector<glm::vec3> chunkPositions;

	/**
	 *  @brief Treshold for LOD.
	 */
	static const float LODTreshold;

	/**
	 * @brief Bottom grass blade color.
	 */
	glm::vec3 bottomGrassColor;

	/**
	 * @brief .Top grass blade color.
	 */
	glm::vec3 topGrassColor;

	/**
	 * Check if chunk is inside camera's frustum.
	 */
	bool isChunkInsideFrustum( const glm::vec3& chunkPosition) const;
};
