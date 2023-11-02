#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace sne::graphics
{
	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);

		~Shader();
		void use() const;

		void Shader::setMat4(const std::string& name, const glm::mat4& value) const;
		void Shader::setVec3(const std::string& name, const glm::vec3& value) const;

	private:
		unsigned int shaderID;

		static void readFromFile(const std::string& filePath, std::string& source);
		static void createShader(unsigned int& shaderID, const char* vertexCode, const char* fragmentCode);
	};
}