#include "dpch.h"
#include "Texture.h"

#include "Dark/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Dark {

	Ref<Texture2D> Texture2D::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: DARK_CORE_ASSERT(false, "Rendering API NONE, Error!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(filePath);

		}

		DARK_CORE_ASSERT(false, "UnKnown Rendering API, Error!");
		return nullptr;
	}

}