#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "architecture/Component.h"

namespace saintNecEngine::graphics
{
	class Cube: public Component
	{
	public:

		Cube();
		~Cube();

		void update() override;
		void draw() const override;

	private:
		unsigned int VBO; // Vertex data
		unsigned int VAO;
		unsigned int EBO; // Indices data
		unsigned int vertexShader;
		unsigned int fragmentShader;
		unsigned int shaderProgram;

	};
	
}