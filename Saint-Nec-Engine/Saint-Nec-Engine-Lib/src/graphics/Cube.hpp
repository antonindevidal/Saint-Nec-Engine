#pragma once
/**
 * @file Cube.hpp
 * @brief Cube graphic component header.
 * @author Antonin DEVIDAL
 * @date november 2nd 2023
 *
 * Cube graphic component.
 *
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>

#include "architecture/SceneManager.hpp"
#include "architecture/Component.hpp"
#include "GraphicComponent.hpp"
#include "graphics/Shader.hpp"
#include "architecture/GameObject.hpp"

namespace sne::graphics
{
	/**
	* @class Cube
	* @brief Cube graphic component
	*/
	class Cube : public GraphicComponent
	{
	public:
		/**
		*
		* Create multicolor cube of size 1*1*1.
		*
		* @param vertexShaderPath Path of the vertex shader.
		* @param fragmentShaderPath Path of the fragment shader.
		*/
		Cube(const char* vertexShaderPath, const char* fragmentShaderPath);

		Cube(const char* vertexShaderPath, const char* fragmentShaderPath, glm::vec3 color, const int& sizeX, const int sizeY, const int sizeZ);

		/**
		*
		* Create a cube of size 1*1*1 of a specific color.
		*
		* @param vertexShaderPath Path of the vertex shader.
		* @param fragmentShaderPath Path of the fragment shader.
		* @param color RGB color of cube.
		*/
		Cube(const char* vertexShaderPath, const char* fragmentShaderPath, glm::vec3 color);
	};
}