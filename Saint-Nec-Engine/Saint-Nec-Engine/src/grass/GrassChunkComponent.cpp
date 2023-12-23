#include "GrassChunkComponent.hpp"

const float GrassChunkComponent::LODTreshold = 50.0f;


GrassChunkComponent::GrassChunkComponent(const int& size, const int& chunkSize, const int nbInstancesPerChunk, const char* vertexShaderPath, const char* fragmentShaderPath)
	:GraphicComponent(vertexShaderPath, fragmentShaderPath), nbInstancesPerChunk(nbInstancesPerChunk),chunkSize(chunkSize), chunkPositions()
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
	

	glm::vec3 bottomColor{ 0.0f, 0.44f, 0.02f, };
	glm::vec3 topColor{ 0.56f, 0.94f, 0.32f, };

	shader.setVec3("grassColorTop", topColor);
	shader.setVec3("grassColorBottom", bottomColor);




	

	for (int i = 0; i < size / chunkSize; i++)
	{
		for (int j = 0; j < size / chunkSize; j++)
		{
			chunkPositions.push_back({ i * chunkSize,0.0f, j * chunkSize });
		}
	}
	std::vector<float> positions;
	int sqrtInstances = sqrt(nbInstancesPerChunk);
	for (int i = 0; i < nbInstancesPerChunk; i++)
	{
		positions.push_back((i % sqrtInstances) * (chunkSize * 1.0 / sqrtInstances) + (std::rand() * 1.0f / (RAND_MAX * chunkSize)));
		positions.push_back(0.0f);
		positions.push_back((i / sqrtInstances) * (chunkSize * 1.0 / sqrtInstances) + (std::rand() * 1.0f / (RAND_MAX * chunkSize)));
	}
	genLOD1(chunkSize, positions);
	genLOD2(chunkSize, positions);

	hasGeometry = true;
	testDir = 0.0f;

	//Level of detail 2
}



void GrassChunkComponent::update()
{
	GraphicComponent::update();
	//testDir += 0.001f;

}

void GrassChunkComponent::genLOD1(const int& chunkSize, const std::vector<float>& positions)
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

	// Level of detail 1
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


}

void GrassChunkComponent::genLOD2(const int& chunkSize, const std::vector<float>& positions)
{
	/*
				  4
				XXXX
			  XXX  XX
			 XX     XX
			XX        X
		   XX         XX  
		   X           X
		  X            XX
		 XX             X  
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
	std::vector<float> vertices = {
		//POSTION				UV
		0.0f , 0.0f ,	0.0f,	0.0f, 0.0f,
		0.1f , 0.0f ,	0.0f,	0.0f, 0.0f,
		0.0f, 0.25f,	0.0f,	0.0f, 0.47f,
		0.1f, 0.25f,	0.0f,	0.0f, 0.47f,
		0.05f, 0.53f,	0.0f,	0.0f, 1.0f,
	};
	std::vector<int> indices = {
		2, 3, 1,
		1, 0, 2,
		4, 3, 2,
	};

	// Level of detail 1
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2); // Generate VBO
	glGenBuffers(1, &EBO2); // generate EBO

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2); // Set type of Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &instanceVBO2);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1);
	renderedElementCount2 = indices.size();
}

void GrassChunkComponent::draw() const
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
		shader.setVec3("windDir", { cos(testDir),0.0f, sin(testDir) });
		shader.setFloat("time", Time::getTimeSinceStart());
		//std::cout << Time::getTimeSinceStart() << std::endl;
		shader.setVec3("camViewDir", sne::SceneManager::getInstance()->getCurrentScene()->getCamera().getFront());
		shader.setMat4("view", sne::SceneManager::getInstance()->getCurrentScene()->getView());
		shader.setMat4("model", parent->getModel());

		glm::vec3 camPosition = sne::SceneManager::getInstance()->getCurrentScene()->getCamera().getPosition();


		//Creating bounding box
		glm::vec4 p00Bottom { 0.0f, 0.0f, 0.0f, 1.0f };
		glm::vec4 p01Bottom { 0.0f, 0.0f, 0.0f, 1.0f };
		glm::vec4 p10Bottom { 0.0f, 0.0f, 0.0f, 1.0f };
		glm::vec4 p11Bottom { 0.0f, 0.0f, 0.0f, 1.0f };

		glm::vec4 p00Top { 0.0f, 1.0f, 0.0f, 1.0f };
		glm::vec4 p01Top { 0.0f, 1.0f, 0.0f, 1.0f };
		glm::vec4 p10Top { 0.0f, 1.0f, 0.0f, 1.0f };
		glm::vec4 p11Top { 0.0f, 1.0f, 0.0f, 1.0f };

		int nbRendered = 0;
		for (const glm::vec3& chunk: chunkPositions)
		{
			shader.setVec3("offset", chunk);
			float dist = glm::distance(chunk,camPosition);
			if (isChunkInsideFrustum(chunk))
			{
				nbRendered++;
				if (dist < LODTreshold)
				{
					glBindVertexArray(VAO);
					glDrawElementsInstanced(GL_TRIANGLES, renderedElementCount, GL_UNSIGNED_INT, 0, nbInstancesPerChunk);
					glBindVertexArray(0);
				}
				else
				{
					glBindVertexArray(VAO2);
					glDrawElementsInstanced(GL_TRIANGLES, renderedElementCount2, GL_UNSIGNED_INT, 0, nbInstancesPerChunk);
					glBindVertexArray(0);
				}
			}
		}
		std::cout << "Nbrendered " << nbRendered << std::endl;
	}
}

bool GrassChunkComponent::isChunkInsideFrustum( const glm::vec3& chunkPosition) const
{
	const sne::Scene* currentScene = (sne::SceneManager::getInstance())->getCurrentScene();
	
	//Bounding box for grass chunk
	glm::vec4 p00Bottom{ chunkPosition.x			, 0.0f, chunkPosition.z, 1.0f };
	glm::vec4 p01Bottom{ chunkPosition.x + chunkSize, 0.0f, chunkPosition.z, 1.0f };
	glm::vec4 p10Bottom{ chunkPosition.x			, 0.0f, chunkPosition.z + chunkSize, 1.0f };
	glm::vec4 p11Bottom{ chunkPosition.x + chunkSize, 0.0f, chunkPosition.z + chunkSize, 1.0f };

	glm::vec4 p00Top{ chunkPosition.x				, 1.0f, chunkPosition.z, 1.0f };
	glm::vec4 p01Top{ chunkPosition.x + chunkSize	, 1.0f, chunkPosition.z, 1.0f };
	glm::vec4 p10Top{ chunkPosition.x				, 1.0f, chunkPosition.z + chunkSize, 1.0f };
	glm::vec4 p11Top{ chunkPosition.x + chunkSize	, 1.0f, chunkPosition.z + chunkSize, 1.0f };


	return  currentScene->isPointInsideViewFrustum(p00Bottom) ||
			currentScene->isPointInsideViewFrustum(p01Bottom) ||
			currentScene->isPointInsideViewFrustum(p10Bottom) ||
			currentScene->isPointInsideViewFrustum(p11Bottom) ||
			currentScene->isPointInsideViewFrustum(p00Top) ||
			currentScene->isPointInsideViewFrustum(p01Top) ||
			currentScene->isPointInsideViewFrustum(p10Top) ||
			currentScene->isPointInsideViewFrustum(p11Top);
}

