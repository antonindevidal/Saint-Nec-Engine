#pragma once
/**
 * @file GraphicComponent.hpp
 * @brief GraphicComponent class.
 * @author Antonin DEVIDAL
 * @date November 10 2023
 *
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <stb_image.h>

#include "Shader.hpp"
#include "../architecture/Time.hpp"
#include "../architecture/Component.hpp"

namespace sne::graphics
{
	/**
	 * All the types of vertex data.
	 */
	enum VertexDataType
	{
		SNE_VERTICES, // 3 floats
		SNE_VERTICES_TEXTURE, // 3 floats + 2 floats
		SNE_VERTICES_COLOR, //3 floats + 3 floats
		SNE_VERTICES_COLOR_TEXTURE //3 floats + 3 floats + 2 floats
	};

	/**
	 * @class GraphicComponent
	 * @brief This class abstracts EBO VBO VAO draw call and Shader uniforms
	 *
	 * This class only uses triangles as primitives.
	 */
	class GraphicComponent : public sne::Component
	{
	public:
		/**
		 * @brief Constructor.
		 *
		 * @param vertexShaderPath Path of the vertex shader.
		 * @param fragmentShaderPath Path of the fragment shader.
		 */
		GraphicComponent(const char* vertexShaderPath, const char* fragmentShaderPath);
		GraphicComponent(const char* vertexShaderPath, const char* fragmentShaderPath, const char* tessellationControlPath, const char* tessellationEvaluationPath);


		~GraphicComponent();


		/**
		* @brief Set the geometry of the graphic component
		*
		* @param vertices Vertex data for the instance.
		* @param vertexDataType Type of vertex data used for the instance.
		* @param indices Geometry indices.
		*/
		void setGeometry(const std::vector<float>& vertices, const VertexDataType& vertexDataType, const std::vector<int>& indices);

		/**
		 * @brief Add a texture for the graphic component.
		 *
		 * @param texturePath Path for the texture.
		 * @param name Name for the uniform inside the shader.
		 */
		void addTexture(const char* texturePath, const char* name);

		void addCubeMap(const std::vector<std::string>& texturesPath);

		/**
		* @brief Draw the cube instance.
		*/
		void draw() const override;

		/**
		 * @brief Getter for the shader object.
		 * 
		 * @return shader instance
		 */
		const Shader& getShader();

	protected:
		/**
		* Vertex Buffer Object.
		*/
		unsigned int VBO;

		/**
		* Vertex Array Object.
		*/
		unsigned int VAO;

		/**
		* Element Buffer Object.
		*/
		unsigned int EBO;

		/**
		 * Number of elements to be rendered (points).
		 */
		unsigned int renderedElementCount;

		/**
		 * Shader object for graphic component.
		 */
		Shader shader;

		/**
		 * Ids for all the textures
		 */
		std::vector<unsigned int> textureIDs;

		unsigned int cubeMapID;

		/**
		 * Has the texture been set.
		 */
		bool hasTexture;

		/**
		 * Has CubeMap..
		 */
		bool hasCubeMap;

		bool hasEBO;

		/**
		 * has the geometry been set.
		 */
		bool hasGeometry;
	};
}

