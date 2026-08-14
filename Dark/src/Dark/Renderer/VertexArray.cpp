#include "dpch.h"
#include "VertexArray.h"

#include "Dark/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Dark {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::None: DARK_CORE_ASSERT(false, "Rendering API NONE, Error!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		DARK_CORE_ASSERT(false, "Unknown Rendering API, ERROR!");
		return nullptr;
	}

}