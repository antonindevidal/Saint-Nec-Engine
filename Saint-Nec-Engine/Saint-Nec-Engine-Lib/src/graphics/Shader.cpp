#include "Shader.hpp"

namespace sne::graphics
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		std::string vertexCode{}, fragmentCode{};

		readFromFile(vertexPath, vertexCode);
		readFromFile(fragmentPath, fragmentCode);
	
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		createShader(shaderID, vShaderCode, fShaderCode);
	}

	Shader::~Shader()
	{
		glDeleteProgram(shaderID);
	}

	void Shader::use() const
	{
		glUseProgram(shaderID);
	}

	void Shader::setMat4(const std::string& name, const glm::mat4& value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, glm::value_ptr(value));
	}

	void Shader::setInt(const std::string& name, const int& value) const
	{
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
	}

	const unsigned int& Shader::getID() const
	{
		return shaderID;
	}

	

	void Shader::readFromFile(const std::string& filePath, std::string& sourceCode)
	{
		int success;
		char infoLog[512];

		std::ifstream shaderStream;
		std::stringstream codeStream;
		try
		{
			shaderStream.open(filePath);
			codeStream << shaderStream.rdbuf();
			sourceCode = codeStream.str();
			shaderStream.close();
		}
		catch(std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: "<< filePath << std::endl;
		}
	}

	void Shader::createShader(unsigned int& shaderID, const char* vertexCode, const char* fragmentCode)
	{
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << std::endl << infoLog << std::endl;
		};

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << std::endl << infoLog << std::endl;
		};

		shaderID = glCreateProgram();
		glAttachShader(shaderID, vertex);
		glAttachShader(shaderID, fragment);
		glLinkProgram(shaderID);
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	

}
