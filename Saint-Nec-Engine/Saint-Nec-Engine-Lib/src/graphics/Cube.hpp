#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>

#include "architecture/SceneManager.h"
#include "architecture/Component.h"
#include "graphics/Shader.hpp"
#include "architecture/GameObject.h";

namespace sne::graphics
{
	class Cube: public Component
	{
	public:

		Cube(const char* vertexShaderPath, const char* fragmentShaderPath);
		Cube(const char* vertexShaderPath, const char* fragmentShaderPath, const char* texturePath);
		Cube(const char* vertexShaderPath, const char* fragmentShaderPath, glm::vec3 color);

		~Cube();

		void update() override;
		void draw() const override;


	private:
		unsigned int VBO; // Vertex data
		unsigned int VAO;
		unsigned int EBO; // Indices data
		unsigned int texture;

		Shader shader;
	};
	
}