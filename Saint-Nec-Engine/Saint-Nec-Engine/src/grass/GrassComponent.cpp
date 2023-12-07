#include "GrassComponent.hpp"



GrassComponent::GrassComponent(const char* vertexShaderPath, const char* fragmentShaderPath)
	:GraphicComponent(vertexShaderPath,fragmentShaderPath)
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

	setGeometry(vertices,sne::graphics::VertexDataType::SNE_VERTICES_TEXTURE,indices);
}


