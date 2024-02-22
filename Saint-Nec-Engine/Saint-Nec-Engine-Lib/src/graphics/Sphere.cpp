#include "Sphere.hpp"

namespace sne::graphics
{
	Sphere::Sphere(const char* vertexShaderPath, const char* fragmentShaderPath): GraphicComponent(vertexShaderPath,fragmentShaderPath)
	{
		std::vector<float> vertices = {
			-0.5f, -0.5f,0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f,0.0f, 0.0f, 1.0f,
			0.5f, 0.5f,0.0f, 1.0f, 1.0f,
			0.5f, -0.5f,0.0f, 1.0f, 0.0f,
		};
		std::vector<int> indices = {
			0, 1, 2,
			2, 3, 0,
		};
		setGeometry(vertices, VertexDataType::SNE_VERTICES_TEXTURE, indices);
	}
}
