#pragma once

namespace Dark {

	class DARK_API Shader {

	private:
		uint32_t m_RendererID{};

	public:
		Shader(const std::string& vertexShaderFP, const std::string& fragmentShaderFP);
		~Shader();

		void Bind() const;
		void UnBind() const;

	
	private:

		std::string parseShader(const std::string& filepath);
		uint32_t CompileShader(const std::string& vertexShaderFP, const std::string& fragmentShaderFP);
		bool CheckCompileError(const std::string& shaderType, uint32_t shader);
	};

}