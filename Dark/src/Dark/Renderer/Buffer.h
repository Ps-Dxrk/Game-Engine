#pragma once

namespace Dark {

	//VertexBuffer Interface, to be implemented by the platform specific rendering APIs to be set up by them
	class VertexBuffer 
	{
		
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};


	//index buffer interface, to be implemented by the platform specific rendering APIs and to be set up by them
	class IndexBuffer
	{

	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

}