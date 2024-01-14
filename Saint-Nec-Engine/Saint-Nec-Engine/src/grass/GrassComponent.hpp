#pragma once
/**
 * @file GrassComponent.hpp
 * @brief Manage grass field with instancing.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date january 14th 2024.
 *
 */

#include <graphics/GraphicComponent.hpp>

 /**
 *	@class GrassComponent.
 *	@brief Manage grass field with instancing.
 */
class GrassComponent : public sne::graphics::GraphicComponent
{
public:
	/**
	 * Constructor for GrassComponent.
	 */
	GrassComponent(const int& width, const int& depth, const int nbInstances, const char* vertexShaderPath, const char* fragmentShaderPath);
	
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

private:
	/**
	 * @brief Instance VBO for geometry.
	 */
	unsigned int instanceVBO;

	/**
	 * Number of grass blade.
	 */
	int nbInstances;

	/**
	* @brief Bottom grass blade color.
	*/
	glm::vec3 bottomGrassColor;

	/**
	* @brief Top grass blade color.
	*/
	glm::vec3 topGrassColor;
};
