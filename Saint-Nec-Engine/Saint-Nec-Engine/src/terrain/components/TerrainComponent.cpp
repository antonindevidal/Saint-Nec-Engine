#include "TerrainComponent.hpp"

TerrainComponent::TerrainComponent(const char* heightmapPath, const char* vertexShaderPath , const char* fragmentShaderPath
	, const unsigned int& terrainWidth, const unsigned int& terrainDepth, const unsigned int& density): terrainDepth(terrainDepth), terrainWidth(terrainWidth), vertices(), indices(), shader(vertexShaderPath, fragmentShaderPath)
{
	/*	
	//Image Loading
	int textWidth, textHeight, nrChannels;

	glGenTextures(1, &heightmapID);
	glBindTexture(GL_TEXTURE_2D, heightmapID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(heightmapPath, &textWidth, &textHeight, &nrChannels, 0);
	
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textWidth, textHeight, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Texture loaded correctly" << std::endl;
	}
	else
	{
		std::cout << "ERROR::TEXTURE::FILE_NOT_SUCCESFULLY_READ: " << heightmapPath << std::endl;
	}


	stbi_image_free(data);
	*/
	//Plane generation
	for (unsigned int i = 0; i < terrainWidth +1; i++)
	{
		for (unsigned int j = 0; j < terrainDepth + 1; j++)
		{
			//Create every vertices

			vertices.push_back( i * 1.0f  - (terrainWidth/2.0f)   );
			vertices.push_back(0.0f); // Can be removed for optimization
			vertices.push_back( j * 1.0f - (terrainDepth/ 2.0f) );
		}
	}

	for (unsigned int i = 0; i < terrainWidth; i++)
	{
		for (unsigned int j = 0; j < terrainDepth; j++)
		{
			//Create every indices (2 triangles per quad)
			indices.push_back( i * (terrainDepth + 1)+ j);
			indices.push_back((i + 1) * (terrainDepth +1 ) + j );
			indices.push_back((i + 1) * (terrainDepth + 1) + j + 1);
			
			indices.push_back((i + 1) * (terrainDepth + 1) + j + 1);
			indices.push_back(i * (terrainDepth + 1) + j +1);
			indices.push_back(i * (terrainDepth + 1) + j);

		}
	}
	
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); // Generate VBO
	glGenBuffers(1, &EBO); // generate EBO

	glBindVertexArray(VAO);
	

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Set type of Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	
	//interpret vertex data array (position)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	shader.use(); //Set default value for matrices
	shader.setMat4("projection", sne::SceneManager::getInstance()->getCurrentScene().getProjection()); //Set projection matrice once because it never changes 
	shader.setMat4("view", sne::SceneManager::getInstance()->getCurrentScene().getView());
	
}

TerrainComponent::~TerrainComponent()
{
	Component::~Component();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void TerrainComponent::update()
{
}

void TerrainComponent::draw() const
{
	
	//glBindTexture(GL_TEXTURE_2D, heightmapID);

	shader.use();

	shader.setMat4("view", sne::SceneManager::getInstance()->getCurrentScene().getView());
	shader.setMat4("model", parent->getModel());

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, terrainDepth * terrainWidth * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}
