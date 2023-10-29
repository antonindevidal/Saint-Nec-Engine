#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace sne::graphics
{
	class Shader
	{
	public:
		Shader();
		Shader(const char* vertexPath, const char* fragmentPath);

		~Shader();
		void use() const;


	private:
		unsigned int shaderID;

		static void readFromFile(const std::string& filePath, std::string& source);
		static void createShader(unsigned int& shaderID, const char* vertexCode, const char* fragmentCode);

	};


}