#include<GLengine/OpenGL/OpenGLShader.h>
namespace GLengine {

	OpenGLShader::OpenGLShader(std::string shaderSource) {
		CompileShaders(shaderSource);
	}

	bool OpenGLShader::CompileVertexShader(std::string& shaderSource, unsigned int& shaderRef) {
		const char* shaderCode = ExtractShaderSource(ShaderType::Vertex, shaderSource);
		return CompileShader(GL_VERTEX_SHADER, shaderRef, shaderCode);
	}

	bool OpenGLShader::CompileFragmentShader(std::string& shaderSource, unsigned int& shaderRef) {
		const char* shaderCode = ExtractShaderSource(ShaderType::Fragment, shaderSource);
		return CompileShader(GL_FRAGMENT_SHADER, shaderRef, shaderCode);
	}

	bool OpenGLShader::CompileShader(GLenum shaderType, unsigned int& shaderRef, const char* shaderSource) {
		
		int compilationSuccess;
		char log[512];

		shaderRef = glCreateShader(shaderType);
		glShaderSource(shaderRef, 1, &shaderSource, NULL);
		glCompileShader(shaderRef);
		glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &compilationSuccess);

		if (!compilationSuccess) {
			glGetShaderInfoLog(shaderRef, 512, NULL, log);
			LogError("VERTEX SHADER COMPILATION FAILED");
			LogError((std::string("[") + std::string(shaderSource) + std::string("]")).c_str());
			LogError(log);
			return false;
		}

		return true;
	}

	bool OpenGLShader::LinkShaderProgram(unsigned int& vertShader, unsigned int& fragShader) {
		int linkingSuccess;
		char log[512];
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertShader);
		glAttachShader(shaderProgram, fragShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkingSuccess);
		if (!linkingSuccess) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, log);
			LogError("SHADER LINKING FAILED");
			LogError(log);
			return false;
		}

		return true;
	}

	void OpenGLShader::CompileShaders(std::string shaderSource) {
		unsigned int vertexShader=0;
		unsigned int fragmentShader=0;

		//compile vertex shader
		if (!CompileVertexShader(shaderSource, vertexShader)) {
			return;
		}
		
		//compile fragment shader
		if (!CompileFragmentShader(shaderSource, fragmentShader)) {
			return;
		}

		LinkShaderProgram(vertexShader, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(shaderProgram);
	}

	void OpenGLShader::UseShader() {
		glUseProgram(shaderProgram);
	}

	void OpenGLShader::Unbind() {
		glUseProgram(0);
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