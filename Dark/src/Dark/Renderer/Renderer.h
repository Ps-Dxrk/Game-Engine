#pragma once

#include "Dark/Renderer/RendererAPI.h"
#include "Dark/Renderer/RenderCommand.h"

//TEMP STUFF
#include "OrthoGraphicCamera.h"
#include "Shader.h"
//

namespace Dark {

	class Renderer {

	private:

		struct SceneData {
			glm::mat4 m_ProjectionViewMatrix;
		};

		static SceneData* s_SceneData;

	public:

		//TODO: Add Parameters for various stuff
		static void BeginScene(OrthoGraphicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		inline static void SetAPI(RendererAPI::API api) { RendererAPI::SetAPI(api); }

	};

}