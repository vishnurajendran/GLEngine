#include<GLengine/OpenGL/OpenGLShader.h>
namespace GLengine {

	OpenGLShader::OpenGLShader(std::string shaderSource) {
		CompileShaders(shaderSource);
	}

	void OpenGLShader::CompileShaders(std::string shaderSource) {

		unsigned int vertexShader;
		unsigned int fragmentShader;

		int compilationSuccess;
		int linkingSuccess;
		char log[512];

		const char* vShaderSource = ExtractShaderSource(ShaderType::Vertex, shaderSource);
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1,&vShaderSource, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compilationSuccess);

		if (!compilationSuccess) {
			glGetShaderInfoLog(vertexShader, 512, NULL, log);
			LogError("VERTEX SHADER COMPILATION FAILED");
			LogError((std::string("[") + std::string(vShaderSource) + std::string("]")).c_str());
			LogError(log);
			return;
		}

		const char* fShaderSource = ExtractShaderSource(ShaderType::Fragment, shaderSource);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compilationSuccess);

		if (!compilationSuccess) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, log);
			LogError("FRAGMENT SHADER COMPILATION FAILED");
			LogError((std::string("[") + std::string(fShaderSource) + std::string("]")).c_str());
			LogError(log);
			return;
		}

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkingSuccess);
		if (!linkingSuccess) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, log);
			LogError("SHADER LINKING FAILED");
			LogError(log);
			return;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(shaderProgram);
	}

	void OpenGLShader::UseShader() {
		glUseProgram(shaderProgram);
	}

	void OpenGLShader::SetBool(const char* attribName, bool value) {
		glUniform1i(glGetUniformLocation(shaderProgram, attribName), (int)value);
	}

	void OpenGLShader::SetInt(const char* attribName, int value) {
		glUniform1i(glGetUniformLocation(shaderProgram, attribName), value);
	}

	void OpenGLShader::SetFloat(const char* attribName, float value) {
		glUniform1f(glGetUniformLocation(shaderProgram, attribName), value);
	}

	void OpenGLShader::SetMatrix4f(const char* attribName, float* matrixPtr) {
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, attribName);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, matrixPtr);
	}

	void OpenGLShader::SetUniform4f(const char* attribName, glm::vec4 val) {
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, attribName);
		glUniform4f(transformLoc, val.x, val.y, val.z, val.w);
	}

}