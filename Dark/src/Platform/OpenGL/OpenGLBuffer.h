#pragma once

#include "Dark/Renderer/Buffer.h"

namespace Dark {

	//vertexBufer///////////////////////////////////////

	class OpenGLVertexBuffer : public VertexBuffer 
	{

	private:
		uint32_t m_RendererID;

	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UpdateData(float* vertices, uint32_t size);

	};

	//IndexBuffer////////////////////////////////////////

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;

	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		inline virtual uint32_t GetCount() const override { return m_Count; }

		void UpdateData(uint32_t* indices, uint32_t size);
	};
}