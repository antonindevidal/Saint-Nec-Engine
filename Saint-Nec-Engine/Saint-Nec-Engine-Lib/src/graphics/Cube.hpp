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
#include "graphics/Shader.hpp"
#include "architecture/GameObject.hpp"

namespace sne::graphics
{
	/**
	* @class Cube
	* @brief Cube graphic component
	*/
	class Cube: public Component
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

		/**
		*
		* Create a cube of size 1*1*1 with a texture.
		*
		* @param vertexShaderPath Path of the vertex shader.
		* @param fragmentShaderPath Path of the fragment shader.
		* @param texturePath Path of the texture.
		*/
		Cube(const char* vertexShaderPath, const char* fragmentShaderPath, const char* texturePath);

		/**
		*
		* Create a cube of size 1*1*1 of a specific color.
		*
		* @param vertexShaderPath Path of the vertex shader.
		* @param fragmentShaderPath Path of the fragment shader.
		* @param color RGB color of cube.
		*/
		Cube(const char* vertexShaderPath, const char* fragmentShaderPath, glm::vec3 color);

		/**
		* @brief Destructor of Cube instance.
		*/
		~Cube();

		/**
		* @brief Draw the cube instance.
		*/
		void draw() const override;


	private:
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
		* Texture for the cube.
		*/
		unsigned int texture;

		/**
		* Shader used to draw the cube.
		*/
		Shader shader;
	};
	
}