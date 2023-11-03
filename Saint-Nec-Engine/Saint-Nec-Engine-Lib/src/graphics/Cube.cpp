#include "Cube.hpp"

namespace sne::graphics
{

	Cube::Cube(const char* vertexShaderPath, const char* fragmentShaderPath):shader(vertexShaderPath,fragmentShaderPath),texture(0)
	{
		float vertices[] = {
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
		unsigned int indices[] = { 
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


		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO); // Generate VBO
		glGenBuffers(1, &EBO); // generate EBO

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO); // Set type of Buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//interpret vertex data array (position)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		shader.use(); //Set default value for matrices
		shader.setMat4("projection", SceneManager::getInstance()->getCurrentScene().getProjection()); //Set projection matrice once because it never changes 
		shader.setMat4("view", SceneManager::getInstance()->getCurrentScene().getView());

	}

	Cube::Cube(const char* vertexShaderPath, const char* fragmentShaderPath, const char* texturePath) : Cube(vertexShaderPath, fragmentShaderPath)
	{
		int width, height, nrChannels;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			std::cout << "Texture loaded correctly" << std::endl;
		}
		else
		{
			std::cout << "ERROR::TEXTURE::FILE_NOT_SUCCESFULLY_READ: " << texturePath << std::endl;
		}
		

		stbi_image_free(data);

	}

	Cube::Cube(const char* vertexShaderPath, const char* fragmentShaderPath, glm::vec3 color) :shader(vertexShaderPath, fragmentShaderPath), texture(0)
	{
		float vertices[] = {
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
		unsigned int indices[] = {
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


		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO); // Generate VBO
		glGenBuffers(1, &EBO); // generate EBO

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO); // Set type of Buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//interpret vertex data array (position)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		shader.use(); //Set default value for matrices
		shader.setMat4("projection", SceneManager::getInstance()->getCurrentScene().getProjection()); //Set projection matrice once because it never changes 
		shader.setMat4("view", SceneManager::getInstance()->getCurrentScene().getView());
		shader.setVec3("color", color);
	}

	Cube::~Cube()
	{
		Component::~Component();
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Cube::draw() const
	{		
		glBindTexture(GL_TEXTURE_2D, texture);

		shader.use();

		shader.setMat4("view", SceneManager::getInstance()->getCurrentScene().getView());
		shader.setMat4("model", parent->getModel());

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

