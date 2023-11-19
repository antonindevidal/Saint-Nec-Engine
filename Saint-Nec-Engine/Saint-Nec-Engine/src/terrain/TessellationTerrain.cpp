#include "TessellationTerrain.hpp"

TessellationTerrain::TessellationTerrain(const unsigned int& width, const unsigned int& depth, const unsigned int& density, const char* vertexShaderPath, const char* fragmentShaderPath, const char* tessellationControlPath, const char* tessellationEvaluationPath):
	GraphicComponent::GraphicComponent(vertexShaderPath,fragmentShaderPath,tessellationControlPath, tessellationEvaluationPath)
{
	lightDir = glm::vec3(0.0f, 0.8f, 0.3f);
	shader.use();
	shader.setMat4("projection", sne::SceneManager::getInstance()->getCurrentScene().getProjection()); //Set projection matrice once because it never changes 
	shader.setMat4("view", sne::SceneManager::getInstance()->getCurrentScene().getView());
	shader.setInt("minTess", 1);
	shader.setInt("maxTess", 12);
	shader.setFloat("maxDist", 30);
	shader.setFloat("textureScaling", 300.0f);
	shader.setVec3("lightDir", lightDir);

	std::vector<float> vertices{};
	std::vector<int> indices{};

	//Creation for geometry
	for (unsigned int i = 0; i < (width * density) + 1; i++)
	{
		for (unsigned int j = 0; j < (depth * density) + 1; j++)
		{
			//Create every vertices
			vertices.push_back((i * 1.0f / density) - (width / 2.0f));
			vertices.push_back(0.0f);
			vertices.push_back((j * 1.0f / density) - (depth / 2.0f));

			//Create UV coordinates
			vertices.push_back(i / (width * density * 1.0f));
			vertices.push_back(j / (depth * density * 1.0f));
		}
	}

	for (unsigned int i = 0; i < width * density; i++)
	{
		for (unsigned int j = 0; j < depth * density; j++)
		{
			//Add indices four by four to create a quad patch
			// From bottom left and counter clockwise
			indices.push_back(i * (depth * density + 1) + j + 1);//bottom left
			indices.push_back((i + 1) * (depth * density + 1) + j + 1); //bottom right
			indices.push_back((i + 1) * (depth * density + 1) + j); //Top right
			indices.push_back(i * (depth * density + 1) + j); //Top left
		}
	}
	setGeometry(vertices, sne::graphics::VertexDataType::SNE_VERTICES_TEXTURE, indices);
	glPatchParameteri(GL_PATCH_VERTICES, 4); //Tell opengl we use quad patches instead of triangles

	nbIndices = indices.size();
}


void TessellationTerrain::update()
{
	GraphicComponent::update();

	//lightDir = glm::vec3(glm::cos(Time::getTimeSinceStart()), glm::sin(Time::getTimeSinceStart()), 1.0f);
	//std::cout << lightDir[0] << " " << lightDir[1] << " " << lightDir[2]<< std::endl;
	

}

void TessellationTerrain::draw() const
{
	
	if (hasTexture)
	{
		for (int i = 0; i < textureIDs.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
		}
	}
	if (hasGeometry)
	{
		shader.use();

		shader.setVec3("lightDir", lightDir);
		shader.setMat4("view", sne::SceneManager::getInstance()->getCurrentScene().getView());
		shader.setMat4("model", parent->getModel());
		shader.setVec3("cameraPos", sne::SceneManager::getInstance()->getCurrentScene().getCamera().getPosition());

		glBindVertexArray(VAO);
		glDrawElements(GL_PATCHES, nbIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
