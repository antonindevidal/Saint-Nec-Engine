
#include "GraphicComponent.hpp"

namespace sne::graphics
{
	class Plane : public GraphicComponent
	{
	public:
		Plane(const unsigned int& width, const unsigned int& depth, const unsigned int& density, const char* vertexShaderPath, const char* fragmentShaderPath);
	};
}
