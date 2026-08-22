#include "dpch.h"
#include "OpenGLRendererAPI.h"

namespace Dark {

	void OpenGLRendererAPI::Clear(const glm::vec4& p_Color)
	{
		glClearColor(p_Color.r, p_Color.g, p_Color.b, p_Color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}