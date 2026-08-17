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

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetUniformMatrix("u_ProjectionView", s_SceneData->m_ProjectionViewMatrix);
		shader->SetUniformMatrix("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}