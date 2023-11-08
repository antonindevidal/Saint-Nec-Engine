#include "TerrainComponent.hpp"

TerrainComponent::TerrainComponent(const std::string& heightmapPath, const unsigned int& width, const unsigned int& depth, const unsigned int& density)
{
	//Image Loading
	int width, height, nrChannels;

	glGenTextures(1, &heightmapID);
	glBindTexture(GL_TEXTURE_2D, heightmapID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(heightmapPath, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Texture loaded correctly" << std::endl;
	}
	else
	{
		std::cout << "ERROR::TEXTURE::FILE_NOT_SUCCESFULLY_READ: " << heightmapPath << std::endl;
	}


	stbi_image_free(data);

	//Plane generation

	for (unsigned int i = 0; i < width+1; i++)
	{
		for (unsigned int j = 0; j < height + 1; j++)
		{

		}
	}

}

TerrainComponent::~TerrainComponent()
{
}

void TerrainComponent::update() const
{
}

void TerrainComponent::draw() const
{
}
