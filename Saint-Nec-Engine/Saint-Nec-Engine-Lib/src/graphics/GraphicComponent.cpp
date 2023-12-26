#include "GraphicComponent.hpp"

namespace sne::graphics
{

	GraphicComponent::GraphicComponent(const char* vertexShaderPath, const char* fragmentShaderPath) :
		VBO(0), VAO(0), EBO(0), renderedElementCount(0), shader(vertexShaderPath, fragmentShaderPath),textureIDs(),cubeMapID(), hasTexture(false), hasCubeMap(false), hasEBO(false), hasGeometry(false)
	{
		shader.use();
		shader.setMat4("projection", sne::SceneManager::getInstance()->getCurrentScene().getProjection()); //Set projection matrice once because it never changes 
		shader.setMat4("view", sne::SceneManager::getInstance()->getCurrentScene().getView());
	}

	GraphicComponent::GraphicComponent(const char* vertexShaderPath, const char* fragmentShaderPath, const char* tessellationControlPath, const char* tessellationEvaluationPath):
		VBO(0), VAO(0), EBO(0), renderedElementCount(0), shader(vertexShaderPath, fragmentShaderPath, tessellationControlPath, tessellationEvaluationPath), textureIDs(), cubeMapID(), hasTexture(false),hasCubeMap(false), hasEBO(false), hasGeometry(false)
	{
		shader.use();
		shader.setMat4("projection", sne::SceneManager::getInstance()->getCurrentScene().getProjection()); //Set projection matrice once because it never changes 
		shader.setMat4("view", sne::SceneManager::getInstance()->getCurrentScene().getView());
	}

	void GraphicComponent::setGeometry(const std::vector<float>& vertices, const VertexDataType& vertexDataType, const std::vector<int>& indices)
	{

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO); // Generate VBO
		glGenBuffers(1, &EBO); // generate EBO

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO); // Set type of Buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		if (!indices.empty())
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);
			hasEBO = true;
			renderedElementCount = indices.size();
		}
		else
		{
			renderedElementCount = vertices.size();
		}
		
		switch (vertexDataType)
		{
		case VertexDataType::SNE_VERTICES:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			break;
		case VertexDataType::SNE_VERTICES_TEXTURE:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			break;
		case VertexDataType::SNE_VERTICES_COLOR:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			break;
		case VertexDataType::SNE_VERTICES_COLOR_TEXTURE:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
			break;
		}

		hasGeometry = true;
	}


	void GraphicComponent::addTexture(const char* texturePath, const char* name)
	{
		if (textureIDs.size() > GL_MAX_TEXTURE_IMAGE_UNITS)
		{
			std::cout << "ERROR::ADD TEXTURE::EXCEEDED MAXIMUM NUMBER OF TEXTURE SUPPORTED FOR A GRAPHIC COMPONENT: " << texturePath << std::endl;
		}

		int textWidth, textHeight, nrChannels;
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* data = stbi_load(texturePath, &textWidth, &textHeight, &nrChannels, 0);

		if (data)
		{
			if (nrChannels == 1)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, textWidth, textHeight, 0, GL_RED, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textWidth, textHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textWidth, textHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			std::cout << "Texture loaded correctly " << texturePath << std::endl;
		}
		else
		{
			std::cout << "ERROR::ADD TEXTURE::FILE_NOT_SUCCESFULLY_READ: " << texturePath << " " << stbi_failure_reason()<< std::endl;
		}


		stbi_image_free(data);
		shader.use();
		shader.setInt(name, textureIDs.size());;

		textureIDs.push_back(textureID);
		hasTexture = true;
	}

	void GraphicComponent::addCubeMap(const std::vector<std::string> texturesPath)
	{
		glGenTextures(1, &cubeMapID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID);


		int width, height, nrChannels;
		unsigned char* data;
		for (unsigned int i = 0; i < texturesPath.size(); i++)
		{
			data = stbi_load(texturesPath[i].c_str(), &width, &height, &nrChannels, 0);
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		hasCubeMap = true;

	}

	void GraphicComponent::draw() const
	{
		int i = 0;
		if (hasTexture)
		{
			for (i = 0; i < textureIDs.size(); i ++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
			}
		}
		if (hasCubeMap)
		{
			glActiveTexture(GL_TEXTURE0+ i );
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID);
		}
		if (hasGeometry)
		{
			shader.use();


			shader.setMat4("view", sne::SceneManager::getInstance()->getCurrentScene().getView());
			shader.setMat4("model", parent->getModel());

			glBindVertexArray(VAO);
			if (hasEBO)
			{
				glDrawElements(GL_TRIANGLES, renderedElementCount, GL_UNSIGNED_INT, 0);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, renderedElementCount);
			}
			
			glBindVertexArray(0);
		}
	}
	const Shader& GraphicComponent::getShader()
	{
		return shader;
	}
}
