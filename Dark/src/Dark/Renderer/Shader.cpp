#include "dpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Dark {


	Shader::Shader(const std::string& vertexShaderFP, const std::string& fragmentShaderFP)
	{
		m_RendererID = CompileShader(vertexShaderFP, fragmentShaderFP);
	}

	Shader::~Shader() 
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		//using the program when the shader is bound
		glUseProgram(m_RendererID);
	}

	void Shader::UnBind() const 
	{
		//unusing the program when the shader is unbound
		glUseProgram(0);
	}

	uint32_t Shader::CompileShader(const std::string& vertexShaderFP, const std::string& fragmentShaderFP) {

		//creating the shader in GPU memory
		uint32_t vertex_shader{ glCreateShader(GL_VERTEX_SHADER) };
		uint32_t fragment_shader{ glCreateShader(GL_FRAGMENT_SHADER) };

		//parsing the shader source code from shader source file
		const std::string& vertex_shader_src_string{ parseShader(vertexShaderFP) };
		const std::string& fragment_shader_src_string{ parseShader(fragmentShaderFP) };

		//getting the const char* to the actual string data or shader source in memory
		const char* vertex_shader_src{ vertex_shader_src_string.c_str() };
		const char* fragment_shader_src{ fragment_shader_src_string.c_str() };

		//sending the shader source to the gpu
		glShaderSource(vertex_shader, 1, &vertex_shader_src, nullptr);
		//compiling the shader
		glCompileShader(vertex_shader);
		//error check, if the shader compiles succesfully or not
		bool success{ CheckCompileError("VERTEX", vertex_shader) };
		DARK_CORE_ASSERT(success, "Failed to Compile VertexShader!");

		//sending the shader source to the gpu
		glShaderSource(fragment_shader, 1, &fragment_shader_src, nullptr);
		//compiling the shader
		glCompileShader(fragment_shader);
		//error check, if the shader compiles successfuly or not
		success = CheckCompileError("FRAGMENT", fragment_shader);
		DARK_CORE_ASSERT(success, "Failed to Compile FragmentShader!");

		//creating the program, this is what runs on the gpu and called glUseProgram. It holds the shader
		uint32_t programID{ glCreateProgram() };
		//attaching the shaders
		glAttachShader(programID, vertex_shader);
		glAttachShader(programID, fragment_shader);
		//linking the shader to the program
		glLinkProgram(programID);
		//error check if the program was abe to successully link
		success = CheckCompileError("PROGRAM", programID);
		DARK_CORE_ASSERT(success, "Failed to Link Program!");

		//detaching the shaders from the program
		glDetachShader(programID, vertex_shader);
		glDetachShader(programID, fragment_shader);

		//deleting the shaders
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		//returning the programID, its an handler which points to where the program is stored in the gpu
		return programID;
	}

	std::string Shader::parseShader(const std::string& filepath)
	{
		std::stringstream ss;
		try {
			//file stream to open the file
			std::fstream filestream;
			//setting failbit and badbit exceptions to handle file errors when it fails to open or find the file
			filestream.exceptions(std::fstream::failbit | std::fstream::badbit);

			filestream.open(filepath);
			
			//since its a stream, we are reading the file contents and streaming it to the strignstream
			ss << filestream.rdbuf();

			filestream.close();

		}
		catch (std::fstream::failure& e) {
			//error handling when file fails to open or read data or stuff like that
			DARK_CORE_ERROR("Shader Parsing Failed!\nFilePath: {0}\n{1}", filepath, e.what());
			ss << "";
		}

		//returns the shader source code as string from the shader source file
		return ss.str();
		
	}

	bool Shader::CheckCompileError(const std::string& shaderType, uint32_t shader) {

		int infoLen;
		int success{};

		if (shaderType == "PROGRAM")
		{
			//getting program link status and stores it in success, if it links then its 1 and if no then its 0
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				//getting the link error infolog length in bytes
				glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
				std::vector<char> infolog;
				infolog.resize(infoLen);
				//getting the link error info log to display the error
				glGetProgramInfoLog(shader, infoLen, &infoLen, &infolog[0]);
				DARK_CORE_ERROR("Error Linking Program: {0}", infolog.data());
			}
		}
		else 
		{
			//getting the shader compilation status, if it succeeds then its 1 and if no then 0
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				//getting the shader infolog length in bytes
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
				std::vector<char> infolog;
				infolog.resize(infoLen);
				//getting the shader infolog to display the error
				glGetShaderInfoLog(shader, infoLen, &infoLen, &infolog[0]);
				DARK_CORE_ERROR("Error Compiling {0} Shader\n{1}", shaderType, infolog.data());
				
				//delete the shader
				glDeleteShader(shader);
			}
		}

		return static_cast<bool>(success);

	}

}

/*
* Im Quite Sad and all because my dad told me I have no skills and no talent for this computer shit
* There are kids younger than me who has become successful with AI and comp skills, I told him abt it and asked him to buy me a better pc
* He said they are all skillful and talentful but im nothing, im worthless, i dont have skills or anything like that. This, i'll never forget this
* From my own dad who's supposed to support me, has let me down, no matter, it doesn't mean im gonna stop this journey, i'll show them
*/