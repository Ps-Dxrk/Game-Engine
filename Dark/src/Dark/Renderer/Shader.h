#pragma once

namespace Dark {

	class DARK_API Shader {

	public:
		virtual ~Shader() = default;

		virtual void Bind()	  const = 0;
		virtual void UnBind() const = 0;
		
		static Ref<Shader> Create(const std::string& vertexShaderFP, const std::string& fragmentShaderFP);
	};

}