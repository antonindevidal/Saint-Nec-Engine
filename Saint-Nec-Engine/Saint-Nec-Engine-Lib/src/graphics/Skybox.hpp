#pragma once
/**
 * @file Camera.hpp
 * @brief Camera class definition.
 * @author Antonin DEVIDAL.
 * @date december 26th 2023.
 *
 */
#include <vector>
#include <string>
#include "GraphicComponent.hpp"

namespace sne::graphics
{
	/**
	 * @class Skybox
	 * @brief Skybox object.
	 */
	class Skybox : public GraphicComponent
	{
	public:
		/**
		 * Skybox constructor.
		 * 
		 * @param textures Textures for the cubemap.
		 * @param vertexShaderPath Path of the vertex shader.
		 * @param fragmentShaderPath Path of the fragment shader.
		 */
		Skybox(std::vector<std::string> textures, const char* vertexShaderPath, const char* fragmentShaderPath);

		/**
		 * No logic should happen there.
		 */
		virtual void draw() const;


	private:

		/**
		 * Tetxure ID for cubemap.
		 */
		unsigned int cubeMapTextureId;
	};

}
