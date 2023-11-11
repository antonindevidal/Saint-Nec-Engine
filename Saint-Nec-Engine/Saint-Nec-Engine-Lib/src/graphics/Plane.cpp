#include "Plane.hpp"


namespace sne::graphics
{
	Plane::Plane(const unsigned int& width, const unsigned int& depth, const unsigned int& density, const char* vertexShaderPath, const char* fragmentShaderPath) :
		GraphicComponent::GraphicComponent(vertexShaderPath, fragmentShaderPath)
	{
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
				vertices.push_back(i / (width * density * 1.0));
				vertices.push_back(j / (depth * density * 1.0));
			}
		}

		for (unsigned int i = 0; i < width * density; i++)
		{
			for (unsigned int j = 0; j < depth * density; j++)
			{
				//Create every indices (2 triangles per quad)
				indices.push_back(i * (depth * density + 1) + j);
				indices.push_back((i + 1) * (depth * density + 1) + j);
				indices.push_back((i + 1) * (depth * density + 1) + j + 1);

				indices.push_back((i + 1) * (depth * density + 1) + j + 1);
				indices.push_back(i * (depth * density + 1) + j + 1);
				indices.push_back(i * (depth * density + 1) + j);
			}
		}
		setGeometry(vertices, VertexDataType::SNE_VERTICES_TEXTURE, indices);
	}

}
