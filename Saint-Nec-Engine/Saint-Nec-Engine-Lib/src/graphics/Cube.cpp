#include "Cube.hpp"

namespace sne::graphics
{

	Cube::Cube(const char* vertexShaderPath, const char* fragmentShaderPath):shader(vertexShaderPath,fragmentShaderPath)
	{
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};


		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO); // Generate VBO
		glGenBuffers(1, &EBO); // generate EBO

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO); // Set type of Buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//interpret vertex data array
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		shader.use(); //Set default value for matrices
		shader.setMat4("projection", SceneManager::getInstance()->getCurrentScene().getProjection()); //Set projection matrice once because it never changes 
		shader.setMat4("view", SceneManager::getInstance()->getCurrentScene().getView());

	}


	Cube::~Cube()
	{
		Component::~Component();
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	void Cube::update()
	{

	}

	void Cube::draw() const
	{		
		shader.use();

		shader.setMat4("view", SceneManager::getInstance()->getCurrentScene().getView());
		shader.setMat4("model", parent->getModel());

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

