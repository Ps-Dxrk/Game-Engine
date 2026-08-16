#pragma once

#include <glm/glm.hpp>

namespace Dark {

	class DARK_API Shader {

	private:
		uint32_t m_RendererID{};

	public:
		Shader(const std::string& vertexShaderFP, const std::string& fragmentShaderFP);
		~Shader();

		void Bind() const;
		void UnBind() const;

		//uniforms
		void SetUniformMatrix(const std::string& name, const glm::mat4& mat);

	
	private:

		std::string parseShader(const std::string& filepath);
		uint32_t CompileShader(const std::string& vertexShaderFP, const std::string& fragmentShaderFP);
		bool CheckCompileError(const std::string& shaderType, uint32_t shader);
	};

}