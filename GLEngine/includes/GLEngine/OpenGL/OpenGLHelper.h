#pragma once
#include<GLEngine/Buffers.h>

namespace GLengine {
	int ShaderDataTypeToOpendGLSize(ShaderDataType type) {
		switch(type) {
			case ShaderDataType::Float:
			case ShaderDataType::Int:    return 1;
		
			case ShaderDataType::Float2:
			case ShaderDataType::Int2:   return 2;

			case ShaderDataType::Float3: 
			case ShaderDataType::Int3:   return 3;

			case ShaderDataType::Float4:
			case ShaderDataType::Int4:   return 4;
		
			case ShaderDataType::Mat3:   return 3 * 3;
			case ShaderDataType::Mat4:   return 4 * 4;
		}

		return 0;
	}

	GLenum ShaderDataTypeToGLEnum(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4: 
			case ShaderDataType::Mat3:   
			case ShaderDataType::Mat4:   return GL_FLOAT;

			case ShaderDataType::Int:    
			case ShaderDataType::Int2:   
			case ShaderDataType::Int3:   
			case ShaderDataType::Int4:   return GL_INT;
		}
	}
}