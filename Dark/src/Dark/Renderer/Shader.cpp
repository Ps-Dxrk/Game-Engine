#include "dpch.h"
#include "Shader.h"

#include "Dark/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Dark {

	Ref<Shader> Shader::Create(const std::string& vertexShaderFP, const std::string& fragmentShaderFP)
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: DARK_CORE_ASSERT(false, "Rendering API Cannot be None!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>( vertexShaderFP, fragmentShaderFP );
		}

		DARK_CORE_ASSERT(false, "UnknownRenderingAPI! Error");
		return nullptr;

	}

}