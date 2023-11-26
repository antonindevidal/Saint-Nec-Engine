#pragma once
/**
 * @file TessellatedPlane.hpp
 * @brief TessellatedPlane class.
 * @author Antonin DEVIDAL
 * @date November 26 2023
 *
 */

#include <graphics/GraphicComponent.hpp>
#include <architecture/SceneManager.hpp>

namespace sne::graphics
{
	/**
	 * @class TessellatedPlane
	 * @brief This class create a plane with Tessellation 
	 *
	 * This class only uses triangles as primitives and quads for patches.
	 */
	class TessellatedPlane : public GraphicComponent
	{
	public:
		/**
		 * Constructor for plane.
		 *
		 * @param width Width of the plane.
		 * @param depth Depth of the plane.
		 * @param vertexShaderPath Path of the vertex shader.
		 * @param fragmentShaderPath Path of the fragment shader.
		 * @param tessellationControlPath Path of the Tessellation Control shader.
		 * @param tessellationEvaluationPath Path of the Tessellation Evaluation shader.
		 */
		TessellatedPlane(const unsigned int& width, const unsigned int& depth, const unsigned int& density, const char* vertexShaderPath, const char* fragmentShaderPath, const char* tessellationControlPath, const char* tessellationEvaluationPath);

		/**
		 * Draw method for a tessellation plane.
		 */
		void draw() const override;
	
	private:
		/**
		 * Number of indices for the plane.
		 */
		unsigned int nbIndices;
	};
}
