#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "architecture/SceneManager.h"
#include "architecture/Component.h"
#include "graphics/Shader.hpp"

namespace sne::graphics
{
	class Cube: public Component
	{
	public:

		Cube();
		Cube(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Cube();

		void update() override;
		void draw() const override;

	private:
		unsigned int VBO; // Vertex data
		unsigned int VAO;
		unsigned int EBO; // Indices data

		Shader shader;
	};
	
}