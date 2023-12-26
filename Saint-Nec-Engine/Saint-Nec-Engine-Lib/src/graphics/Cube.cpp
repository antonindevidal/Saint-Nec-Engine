#include "Cube.hpp"

namespace sne::graphics
{

	Cube::Cube(const char* vertexShaderPath, const char* fragmentShaderPath):GraphicComponent(vertexShaderPath,fragmentShaderPath)
	{
		std::vector<float> vertices = {
			//Positions         //Colors            //Texture coords
			-0.5,  0.5,  0.5,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
			 0.5,  0.5,  0.5,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
			 0.5, -0.5,  0.5,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
			-0.5, -0.5,  0.5,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
			-0.5,  0.5, -0.5,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
			 0.5,  0.5, -0.5,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
			 0.5, -0.5, -0.5,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
			-0.5, -0.5, -0.5,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
		};
		std::vector<int> indices= { 
			0, 1, 2,
			2, 3, 0,
			4, 0, 3,
			3, 7, 4,
			5, 4, 7,
			7, 6, 5,
			1, 5, 6,
			6, 2, 1,
			3, 2, 6,
			6, 7, 3,
			4, 5, 1,
			1, 0, 4,
		};

		setGeometry(vertices, VertexDataType::SNE_VERTICES_COLOR_TEXTURE, indices);
	}



	Cube::Cube(const char* vertexShaderPath, const char* fragmentShaderPath, glm::vec3 color) :GraphicComponent(vertexShaderPath, fragmentShaderPath)
	{
		std::vector<float> vertices = {
			//Positions         
			-0.5,  0.5,  0.5,
			 0.5,  0.5,  0.5,
			 0.5, -0.5,  0.5,
			-0.5, -0.5,  0.5,
			-0.5,  0.5, -0.5,
			 0.5,  0.5, -0.5,
			 0.5, -0.5, -0.5,
			-0.5, -0.5, -0.5,
		};
		std::vector<int> indices = {
			0, 1, 2,
			2, 3, 0,
			4, 0, 3,
			3, 7, 4,
			5, 4, 7,
			7, 6, 5,
			1, 5, 6,
			6, 2, 1,
			3, 2, 6,
			6, 7, 3,
			4, 5, 1,
			1, 0, 4,
		};

		setGeometry(vertices, VertexDataType::SNE_VERTICES, indices);
		
		shader.use();
		shader.setVec3("color", color);
		
	}

	Cube::~Cube()
	{
		Component::~Component();
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

}

