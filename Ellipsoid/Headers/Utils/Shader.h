#pragma once

#include <string>

class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::string m_VertexShader;
	std::string m_FragmentShader;

	bool CompileShader(unsigned int type, const std::string& source);
	bool CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	std::string ParseShader(const std::string& filepath);
	unsigned int GetUniformLocation(const std::string& name);
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};

