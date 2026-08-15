#pragma once

#include "Dark/Renderer/RendererAPI.h"
#include "Dark/Renderer/RenderCommand.h"

namespace Dark {

	class Renderer {

	private:

	public:

		//TODO: Add Parameters for various stuff
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);


		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		inline static void SetAPI(RendererAPI::API api) { RendererAPI::SetAPI(api); }

	};

}