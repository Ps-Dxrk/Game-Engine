#pragma once

#include "Dark/Renderer/VertexArray.h"

namespace Dark {

	class OpenGLVertexArray : public VertexArray
	{

		uint32_t m_RendererID;

		//holding references to all the vertexbuffers and also the IndexBuffer
		std::vector<Ref<VertexBuffer>> m_VertexBuffers{};
		Ref<IndexBuffer> m_IndexBuffer{};

	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual inline const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override{ return m_VertexBuffers; }
		virtual inline const Ref<IndexBuffer>& GetIndexBuffer() const override{ return m_IndexBuffer; }

	};

}