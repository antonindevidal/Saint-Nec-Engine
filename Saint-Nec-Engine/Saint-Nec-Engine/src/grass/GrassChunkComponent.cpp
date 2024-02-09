#include "GrassChunkComponent.hpp"
#include <architecture/Time.hpp>
#include <architecture/SceneManager.hpp>
#include <architecture/GameObject.hpp>

const float GrassChunkComponent::LODTreshold = 100.0f;


GrassChunkComponent::GrassChunkComponent(const int& size, const int& chunkSize, const int nbInstancesPerChunk, const char* vertexShaderPath, const char* fragmentShaderPath)
	:GraphicComponent(vertexShaderPath, fragmentShaderPath), nbInstancesPerChunk(nbInstancesPerChunk), chunkSize(chunkSize), chunkPositions()
	,bottomGrassColor({ 43.0 / 255.0, 147.0 / 255.0, 72.0 / 255.0 }), topGrassColor({ 128.0 / 255.0, 185.0 / 255.0, 24.0 / 255.0 })
{

	//Create chunks positions.
	//Ideally this can be pregenerated and read from a file
	for (int i = 0; i < size / chunkSize; i++)
	{
		for (int j = 0; j < size / chunkSize; j++)
		{
			chunkPositions.push_back({ i * chunkSize,0.0f, j * chunkSize });
		}
	}

	std::random_device dev;
	std::mt19937 gen{ dev()};
	std::uniform_real_distribution<float> dist{ -0.1f, 0.1f }; //Distribution for grass offset


	//Create grass blades position for a chunk
	//Ideally this can be pregenerated and read from a file
	std::vector<float> positions;
	int sqrtInstances = sqrt(nbInstancesPerChunk);
	for (int i = 0; i < nbInstancesPerChunk; i++)
	{
		positions.push_back((i % sqrtInstances) * (chunkSize * 1.0 / sqrtInstances) + dist(gen));
		positions.push_back(0.0f);
		positions.push_back((i / sqrtInstances) * (chunkSize * 1.0 / sqrtInstances) + dist(gen));
	}
	//Generate geometry for two levels of LOD
	genLOD1(positions);
	genLOD2(positions);

	hasGeometry = true;

	shader.use();
	shader.setVec3("grassColorTop", topGrassColor);
	shader.setVec3("grassColorBottom", bottomGrassColor);
}



void GrassChunkComponent::update()
{
	GraphicComponent::update();
}

void GrassChunkComponent::genLOD1(const std::vector<float>& positions)
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
	*/
	std::vector<float> vertices = {
		//POSTION				UV				NORMAL
		0.0f , 0.0f , 0.0f,		0.0f, 0.0f,		0.37f, 0.0f, 0.93f,
		0.1f , 0.0f , 0.0f,		0.0f, 0.0f,		-0.37f, 0.0f, 0.93f,
		0.0f , 0.5f, 0.0f,		0.0f, 0.47f,	0.37f, 0.0f, 0.93f,
		0.1f , 0.5f, 0.0f,		0.0f, 0.47f,	-0.37f, 0.0f, 0.93f,
		0.02f, 0.8f , 0.0f,		0.0f, 0.75f,	0.37f, 0.0f, 0.93f,
		0.08f, 0.8f , 0.0f,		0.0f, 0.75f,	-0.37f, 0.0f, 0.93f,
		0.04f, 1.0f, 0.0f,		0.0f, 0.94f,	0.37f, 0.0f, 0.93f,
		0.06f, 1.0f, 0.0f,		0.0f, 0.94f,	-0.37f, 0.0f, 0.93f,
		0.05f, 1.06f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
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



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &instanceVBO);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(3, 1);
	renderedElementCount = indices.size();


}

void GrassChunkComponent::genLOD2(const std::vector<float>& positions)
{
	/*
				  2
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
		XX              XX
		X                X  
		X                X
		X                X
		X                X
		X                X
		X                X
		X                X
		X  0             X   1
	*/
	std::vector<float> vertices = {
		//POSTION				UV							
		0.0f , 0.0f ,	0.0f,	0.0f, 0.0f,		0.37f, 0.0f, 0.93f,
		0.1f , 0.0f ,	0.0f,	0.0f, 0.0f,		0.37f, 0.0f, 0.93f,
		0.05f, 1.06f,	0.0f,	0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	};
	std::vector<int> indices = {
		2, 3, 1,
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



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &instanceVBO2);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(3, 1);
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
		const sne::Scene* currentScene = sne::SceneManager::getInstance()->getCurrentScene();

		//Set Uniforms 
		shader.use();
		shader.setVec3("windDir", { cos(0.7),0.0f, sin(0.7) });
		shader.setVec3("sun", glm::normalize(currentScene->getDirectionnalLight()));
		shader.setFloat("time", Time::getTimeSinceStart());
		shader.setVec3("camViewDir", currentScene->getCamera().getFront());
		shader.setMat4("view", currentScene->getView());
		shader.setMat4("model", parent->getModel());

		glm::vec3 camPosition = currentScene->getCamera().getPosition();

		//Creating bounding box
		glm::vec4 p00Bottom{ 0.0f, 0.0f, 0.0f, 1.0f };
		glm::vec4 p01Bottom{ 0.0f, 0.0f, 0.0f, 1.0f };
		glm::vec4 p10Bottom{ 0.0f, 0.0f, 0.0f, 1.0f };
		glm::vec4 p11Bottom{ 0.0f, 0.0f, 0.0f, 1.0f };

		glm::vec4 p00Top{ 0.0f, 1.0f, 0.0f, 1.0f };
		glm::vec4 p01Top{ 0.0f, 1.0f, 0.0f, 1.0f };
		glm::vec4 p10Top{ 0.0f, 1.0f, 0.0f, 1.0f };
		glm::vec4 p11Top{ 0.0f, 1.0f, 0.0f, 1.0f };

		int nbRendered = 0;
		for (const glm::vec3& chunk : chunkPositions)
		{
			shader.setVec3("offset", chunk);
			float dist = glm::distance(chunk, camPosition);

			
			if (isChunkInsideFrustum(chunk))
			{

				nbRendered++;
				// Select LOD 1 if distance of chunk inferior to the set Treshold
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
	}
}

bool GrassChunkComponent::isChunkInsideFrustum(const glm::vec3& chunkPosition) const
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


	return  currentScene->isPointInsideViewFrustum(parent->getModel() * p00Bottom ) ||
			currentScene->isPointInsideViewFrustum(parent->getModel() * p01Bottom) ||
			currentScene->isPointInsideViewFrustum(parent->getModel() * p10Bottom) ||
			currentScene->isPointInsideViewFrustum(parent->getModel() * p11Bottom) ||
			currentScene->isPointInsideViewFrustum(parent->getModel() * p00Top) ||
			currentScene->isPointInsideViewFrustum(parent->getModel() * p01Top) ||
			currentScene->isPointInsideViewFrustum(parent->getModel() * p10Top) ||
			currentScene->isPointInsideViewFrustum(parent->getModel() * p11Top);
}

