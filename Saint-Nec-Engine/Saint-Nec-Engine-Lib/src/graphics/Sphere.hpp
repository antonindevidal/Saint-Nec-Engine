#pragma once 

#include "GraphicComponent.hpp"

namespace sne::graphics
{
	class Sphere : public GraphicComponent
	{
	public:
		Sphere( const char* vertexShaderPath, const char* fragmentShaderPath);

	};
}
