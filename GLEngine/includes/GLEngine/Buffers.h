#pragma once
#include<string>
#include<list>
#include<vector>
#include<initializer_list>

namespace GLengine {

	enum  class ShaderDataType
	{
		None = 0,
		Float4,
		Float3,
		Float2,
		Float,
		Mat4,
		Mat3,
		Int4,
		Int3,
		Int2,
		Int
	};

	static unsigned int ShaderDataType2Size(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float: return sizeof(float);
			case ShaderDataType::Float2: return sizeof(float) * 2;
			case ShaderDataType::Float3: return sizeof(float) * 3;
			case ShaderDataType::Float4: return sizeof(float) * 4;
			case ShaderDataType::Int: return sizeof(int);
			case ShaderDataType::Int2: return sizeof(int)*2;
			case ShaderDataType::Int3: return sizeof(int)*3;
			case ShaderDataType::Int4: return sizeof(int)*4;
			case ShaderDataType::Mat3: return sizeof(float) * 3 * 3;
			case ShaderDataType::Mat4: return sizeof(float) * 4 * 4;
		}
		return 0;
	}

	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		unsigned int Size;
		unsigned int Offset;
		bool Normalised = false;
		BufferElement(ShaderDataType type, const std::string& name, const bool normalised)
			: Name(name), Type(type), Size(ShaderDataType2Size(type)), Offset(0), Normalised(normalised)
		{
		}
	};

	class BufferLayout {
	private:
		std::vector<BufferElement> elements;
		unsigned int stride = 0;		
		void CalculateStrideAndOffset() {
			unsigned int offset = 0;
			stride = 0;
			for (auto& element : elements) {
				element.Offset = offset;
				offset += element.Size;
				stride += element.Size;
			}
		}

	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements)
		: elements(elements)
		{
			CalculateStrideAndOffset();
		}

		inline unsigned int Stride() { return stride; }
		inline const std::vector<BufferElement>& GetElements() const { return elements; }
		inline std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return elements.end(); }
	};

	class VertexBuffer {
	protected:
		unsigned int length;
		BufferLayout* layout;
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetLayout(BufferLayout& layout) = 0;
		virtual BufferLayout& GetLayout() = 0;
		inline unsigned int GetLength() { return length; }
		static VertexBuffer* CreateBuffer(float* vertices, unsigned int count);
	};

	class IndexBuffer {
	protected:
		unsigned int length;
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		inline unsigned int GetLength() { return length; }
		static IndexBuffer* CreateBuffer(unsigned int* indices, unsigned int count);
	};
}