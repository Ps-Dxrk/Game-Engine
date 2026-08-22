#pragma once

#include "Dark/Renderer/RendererAPI.h"

namespace Dark {

	class RenderCommand
	{
		static RendererAPI* s_RendererAPI;

	public:

		inline static void Clear(const glm::vec4& p_Color)
		{
			s_RendererAPI->Clear(p_Color);
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	};

}