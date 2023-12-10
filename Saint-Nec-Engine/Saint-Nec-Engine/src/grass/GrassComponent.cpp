#include "GrassComponent.hpp"



GrassComponent::GrassComponent(const int & width, const int & depth, const int nbInstances, const char* vertexShaderPath, const char* fragmentShaderPath)
	:GraphicComponent(vertexShaderPath,fragmentShaderPath), nbInstances(nbInstances)
{
	/*
				  8
				XXXX
			  XXX  XX
			 XX     XX
			XXXXXXXXXXX
		   XX 6       XX  7
		   X           X
		  XXXXXXXXXXXXXXX
		 XX  4          X  5
		 X              X
		XX              XX
		XXXXXXXXXXXXXXXXXX
		X  2             X  3
		X                X
		X                X
		X                X
		X                X
		X                X
		X                X
		X  0             X   1


	
		We give Grass Color with two colors and mix between bottom and top from UV position

		TODO: Set U position in UV
	*/

	glm::vec3 bottomColor { 0.0f, 0.44f, 0.02f, };
	glm::vec3 topColor { 0.56f, 0.94f, 0.32f, };

	shader.setVec3("grassColorTop", topColor);
	shader.setVec3("grassColorBottom", bottomColor);


	std::vector<float> vertices = {
		//POSTION				UV
		0.0f , 0.0f , 0.0f,		0.0f, 0.0f,
		0.1f , 0.0f , 0.0f,		0.0f, 0.0f,
		0.0f , 0.25f, 0.0f,		0.0f, 0.47f,
		0.1f , 0.25f, 0.0f,		0.0f, 0.47f,
		0.02f, 0.4f , 0.0f,		0.0f, 0.75f,
		0.08f, 0.4f , 0.0f,		0.0f, 0.75f,
		0.04f, 0.50f, 0.0f,		0.0f, 0.94f,
		0.06f, 0.50f, 0.0f,		0.0f, 0.94f,
		0.05f, 0.53f, 0.0f,		0.0f, 1.0f,
	};
	std::vector<int> indices = {
		2, 3, 1,
		1, 0, 2,
		4, 5, 3,
		3, 2, 4,
		6, 7, 5,
		5, 4, 6,
		8, 7, 6
	};

	std::vector<float> positions;
	int sqrtInstances = sqrt(nbInstances);
	for (int i = 0; i < nbInstances; i++)
	{
		positions.push_back((i % sqrtInstances) * (width * 1.0 / sqrtInstances) + (std::rand() * 1.0f / (RAND_MAX * width)));
		positions.push_back(0.0f);
		positions.push_back((i / sqrtInstances) * (width * 1.0 / sqrtInstances) + (std::rand() *1.0f/ (RAND_MAX * depth)));
	}



	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); // Generate VBO
	glGenBuffers(1, &EBO); // generate EBO

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Set type of Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glGenBuffers(1, &instanceVBO);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1);
	

	renderedElementCount = indices.size();
	hasGeometry = true;
}

void GrassComponent::update()
{
	GraphicComponent::update();
}

void GrassComponent::draw() const
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
		//float test = glm::dot(sne::SceneManager::getInstance()->getCurrentScene().getCamera().getFront(), glm::vec3(0.0f, 0.0f, 1.0f));
		//std::cout << 1.0f  - std::abs(test)<< std::endl;


		shader.use();
		shader.setVec3("windDir", glm::vec3(0.0f, 0.0f, 1.0f));
		shader.setFloat("time",Time::getTimeSinceStart());
		//std::cout << Time::getTimeSinceStart() << std::endl;
		shader.setVec3("camViewDir", sne::SceneManager::getInstance()->getCurrentScene().getCamera().getFront());
		shader.setMat4("view", sne::SceneManager::getInstance()->getCurrentScene().getView());
		shader.setMat4("model", parent->getModel());

		glBindVertexArray(VAO);
		glDrawElementsInstanced(GL_TRIANGLES,renderedElementCount, GL_UNSIGNED_INT,0,nbInstances);
		glBindVertexArray(0);
	}
}


