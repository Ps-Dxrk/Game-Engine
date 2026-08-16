#include "dpch.h"
#include "Renderer.h"

namespace Dark {

	Renderer::SceneData* Renderer::s_SceneData{ new SceneData() };

	void Renderer::BeginScene(OrthoGraphicCamera& camera)
	{
		s_SceneData->m_ProjectionViewMatrix = camera.GetProjectionViewMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->SetUniformMatrix("u_ProjectionView", s_SceneData->m_ProjectionViewMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}