#pragma once
#include "Core/Base.h"

class Shader
{
public:
	Shader(const std::string& vertexSource, const std::string& fragmentSource);
	~Shader();

	static uint CompileShader(const std::string& source, uint type);
	static bool GetShaderCompileStatus(uint shaderID, std::string* info);
	int GetUniformLocation(const std::string& variable);
	void SetUniform4f(const std::string& variable, float _1, float _2, float _3, float _4);
	void SetUniform2f(const std::string& variable, float _1, float _2);
	void SetUniform1f(const std::string& variable, float _1);

	void Bind(bool bind);

	static Shader* LoadShader(const std::string& vertexFilePath, const std::string& fragmentFilePath);

private:
	uint ID;
};

