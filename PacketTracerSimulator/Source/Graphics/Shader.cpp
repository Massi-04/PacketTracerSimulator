#include "Shader.h"
#include "Libs/GL/glew.h"
#include "Utils/FileManager.h"

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) : ID(0)
{
	LOG("Shader object created\n");
	uint vertexID = CompileShader(vertexSource, GL_VERTEX_SHADER);
	uint fragmentID = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);
	if (vertexID != 0 && fragmentID != 0)
	{
		ID = glCreateProgram();
		glAttachShader(ID, vertexID);
		glAttachShader(ID, fragmentID);
		glLinkProgram(ID);
		glValidateProgram(ID);
		// cleanup
		glDetachShader(ID, vertexID);
		glDetachShader(ID, fragmentID);
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
	}
}

Shader::~Shader()
{
	glDeleteProgram(ID);
	LOG("Shader object destroyed\n");
}

uint Shader::CompileShader(const std::string& source, uint type)
{
	uint ID = 0;
	std::string compileStatus;
	ID = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(ID, 1, &src, nullptr);
	glCompileShader(ID);
	if (!GetShaderCompileStatus(ID, &compileStatus))
	{
		LOG("[ERROR:] " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader compile error: " << compileStatus);
		return 0;
	}
	return ID;
}

bool Shader::GetShaderCompileStatus(uint shaderID, std::string* info)
{
	int compileResult = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_TRUE)
		return true; // no errors
	int msgLen;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &msgLen);
	char* msg = new char[msgLen];
	glGetShaderInfoLog(shaderID, msgLen, &msgLen, msg);
	if (info != nullptr)
		*info = msg;
	delete[] msg;
	return false;
}

int Shader::GetUniformLocation(const std::string& variable)
{
	return glGetUniformLocation(ID, variable.c_str());
}

void Shader::SetUniform4f(const std::string& variable, float _1, float _2, float _3, float _4)
{
	glProgramUniform4f(ID, GetUniformLocation(variable), _1, _2, _3, _4);
}

void Shader::SetUniform2f(const std::string& variable, float _1, float _2)
{
	glProgramUniform2f(ID, GetUniformLocation(variable), _1, _2);
}

void Shader::SetUniform1f(const std::string& variable, float _1)
{
	glProgramUniform1f(ID, GetUniformLocation(variable), _1);
}

void Shader::Bind(bool bind)
{
	glUseProgram(bind ? ID : 0);
}

Shader* Shader::LoadShader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	Shader* shader = nullptr;
	std::string vertexSource = FileManager::ReadFile(vertexFilePath);
	std::string fragmentSource = FileManager::ReadFile(fragmentFilePath);
	if (!vertexSource.empty() && !fragmentSource.empty())
		shader = new Shader(vertexSource, fragmentSource);
	return shader;
}
