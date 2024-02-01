#pragma once
/**
 * @file Shader.hpp
 * @brief Shader program for a graphic component.
 * @author Antonin DEVIDAL
 * @date november 2nd 2023
 *
 * Shader program for a graphic component.
 *
 */

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace sne::graphics
{
	/**
	* @class Shader
	* @brief Shader program
	*/
	class Shader
	{
	public:
		/**
		 * @brief Create a shader program from files.
		 *
		 * @param vertexPath Path of the vertex shader.
		 * @param fragmentPath Path of the fragment shader.
		 */
		Shader(const char* vertexPath, const char* fragmentPath);

		/**
		 * @brief Create a shader program from files.
		 *
		 * @param vertexPath Path of the vertex shader.
		 * @param fragmentPath Path of the fragment shader.
		 * @param tessellationControlPath Path of the tessellation control shader.
		 * @param tessellationEvaluationPath Path of the tessellation evaluation shader.
		 */
		Shader(const char* vertexPath, const char* fragmentPath, const char* tessellationControlPath, const char* tessellationEvaluationPath);


		/**
		 * @brief Destructor of Shader class.
		 */
		~Shader();

		/**
		 * @brief Bind the shader program.
		 */
		void use() const;

		/**
		 * @brief Set 4x4 Matrix uniform to th shader program.
		 *
		 * @param name Name of the uniform.
		 * @param value Matrix to set.
		 */
		void setMat4(const std::string& name, const glm::mat4& value) const;

		/**
		 * @brief Set Vector 3 uniform to th shader program.
		 *
		 * @param name Name of the uniform.
		 * @param value Vector 3 to set.
		 */
		void setVec3(const std::string& name, const glm::vec3& value) const;
		void setVec2(const std::string& name, const glm::vec2& value) const;

		/**
		 * @brief Set Int uniform to th shader program.
		 *
		 * @param name Name of the uniform.
		 * @param value int to set.
		 */
		void setInt(const std::string& name, const int& value) const;

		/**
		 * @brief Set float uniform to th shader program.
		 *
		 * @param name Name of the uniform.
		 * @param value float to set.
		 */
		void setFloat(const std::string& name, const float& value) const;

		/**
		 * @brief Return the ID of the shader.
		 */
		const unsigned int& getID() const;

	private:
		/**
		 * Shader ID.
		 */
		unsigned int shaderID;

		/**
		 * @brief Read file from path.
		 * 
		 * @param filePath Path to the file to read.
		 * @param source Variable to write the file to.
		 */
		static void readFromFile(const std::string& filePath, std::string& source);

		/**
		 * @brief Create shader program.
		 * 
		 * @param ID of the shader.
		 * @param Code for vertex shader.
		 * @param Code for fragment shader.
		 */
		static void createShader(unsigned int& shaderID, const char* vertexCode, const char* fragmentCode);

		/**
		 * @brief Create shader program.
		 *
		 * @param ID of the shader.
		 * @param Code for vertex shader.
		 * @param Code for fragment shader.
		 * @param Code for tessellation control shader.
		 * @param Code for tessellation evaluation shader.
		 */
		static void createShader(unsigned int& shaderID, const char* vertexCode, const char* fragmentCode, const char* controlCode, const char* evaluationCode);
	};
}