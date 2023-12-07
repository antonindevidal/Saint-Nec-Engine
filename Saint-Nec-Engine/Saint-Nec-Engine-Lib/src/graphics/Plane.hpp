#pragma once
/**
 * @file plane.hpp
 * @brief Plane component class.
 * @author Antonin DEVIDAL
 * @date November 10 2023
 *
 */
#include "GraphicComponent.hpp"

namespace sne::graphics
{
	/**
	 * @class Plane
	 * @brief This class creates a plane graphic component.
	 *
	 */
	class Plane : public GraphicComponent
	{
	public:
		/**
		 * Constructor for plane.
		 *
		 * @param width Width of the plane.
		 * @param depth Depth of the plane.
		 * @param density Number of vertices per unit.
		 * @param vertexShaderPath Path of the vertex shader.
		 * @param fragmentShaderPath Path of the fragment shader.
		 */
		Plane(const unsigned int& width, const unsigned int& depth, const unsigned int& density, const char* vertexShaderPath, const char* fragmentShaderPath);
	};
}
