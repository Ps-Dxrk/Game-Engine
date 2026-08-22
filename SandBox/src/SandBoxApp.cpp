#include "Dark.h"

#include <imgui/imgui.h>

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Dark::Layer
{
private:

	Dark::Ref<Dark::VertexArray> m_SquareVA{};
	Dark::Ref<Dark::Shader> m_Shader{}, m_TextureShader{};
	Dark::Ref<Dark::Texture2D> m_Texture{};

	//bg color
	glm::vec4 bg_clear_color{};

	//camera
	Dark::OrthoGraphicCamera m_Camera;
	glm::vec3 m_CamPos{};
	float m_CamSpeed{5.0f};
	float m_CamRotation{};
	float m_CamRotationSpeed{ 90.0f };

	//color vectors for the squares
	glm::vec4 m_Color{ 0.0f, 0.0f, 1.0f, 1.0f };
public:
	ExampleLayer()
		: Layer("ExampleLayer"), m_Camera{ -3.2f, 3.2f, 1.8f, -1.8f }
	{

		//square
		m_SquareVA = Dark::VertexArray::Create();

		float verticesSQ[20]{
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
			 0.5f, 0.5f, 0.0f,   1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f,   0.0f, 1.0f
		};

		Dark::Ref<Dark::VertexBuffer> squareVB{ Dark::VertexBuffer::Create(verticesSQ, sizeof(verticesSQ)) };

		Dark::BufferLayout layoutSQ
		{
			{"aPos", Dark::ShaderDataType::Float3},
			{"aTexCoords", Dark::ShaderDataType::Float2}
		};

		squareVB->SetLayout(layoutSQ);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t indicesSQ[6]{
			0, 1, 2, 2, 3, 0
		};

		Dark::Ref<Dark::IndexBuffer> squareIB{ Dark::IndexBuffer::Create(indicesSQ, 6) };
		m_SquareVA->SetIndexBuffer(squareIB);

		m_Shader = Dark::Shader::Create("Assets\\Shaders\\vert.glsl", "Assets\\Shaders\\frag.glsl");

		//texture
		m_TextureShader = Dark::Shader::Create("Assets\\Shaders\\texVert.glsl", "Assets\\Shaders\\texFrag.glsl");
		std::static_pointer_cast<Dark::OpenGLShader>(m_TextureShader)->SetUniformInt("u_Texture", 0);

		m_Texture = Dark::Texture2D::Create("Assets\\Textures\\adawong.jpg");

		//camera stuff
		m_Camera.SetPosition(m_CamPos);
	}

	void OnUpdate(Dark::DeltaTime dt) override
	{

		DARK_CLIENT_INFO("DeltaTime: Milliseconds: {0}ms", dt.GetMilliseconds());

		//camera update
		if (Dark::Input::IsKeyPressed(DK_KEY_RIGHT)) m_CamPos.x += m_CamSpeed * dt;
		if (Dark::Input::IsKeyPressed(DK_KEY_LEFT )) m_CamPos.x -= m_CamSpeed * dt;
		if (Dark::Input::IsKeyPressed(DK_KEY_UP   )) m_CamPos.y += m_CamSpeed * dt;
		if (Dark::Input::IsKeyPressed(DK_KEY_DOWN )) m_CamPos.y -= m_CamSpeed * dt;

		if (Dark::Input::IsKeyPressed(DK_KEY_J)) m_CamRotation += m_CamRotationSpeed * dt;
		if (Dark::Input::IsKeyPressed(DK_KEY_L)) m_CamRotation -= m_CamRotationSpeed * dt;
		//

		m_Camera.SetPosition(m_CamPos);
		m_Camera.SetRotation(m_CamRotation);

		Dark::RenderCommand::Clear(bg_clear_color);

		Dark::Renderer::BeginScene(m_Camera);

		std::static_pointer_cast<Dark::OpenGLShader>(m_Shader)->Bind();
		std::static_pointer_cast<Dark::OpenGLShader>(m_Shader)->SetUniformFloat4("u_Color", m_Color);

		const glm::mat4& scale{ glm::scale(glm::mat4{1.0f}, glm::vec3{0.3f}) };
	
		for (int y{}; y++ < 20; ) {
			for (int x{}; x++ < 20; ) {
				glm::vec3 pos{ x * 0.33f, y * 0.33f, 0.0f };
				const glm::mat4& transform{ glm::translate(glm::mat4{1.0f}, pos) * scale };
				Dark::Renderer::Submit(m_Shader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Dark::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4{ 1.0f }, glm::vec3{ 5.0f }));

		Dark::Renderer::EndScene();
	}

	void OnEvent(Dark::Event& e) override
	{
	}

	void OnImGuiRender() override
	{
		ImGui::Begin(m_Name.c_str());
			ImGui::ColorPicker4("BgClearColor", glm::value_ptr(bg_clear_color));

			ImGui::ColorEdit3("Tile Color", glm::value_ptr(m_Color));

		ImGui::End();
	}
};

class Sandbox : public Dark::Application
{

public:
	Sandbox() 
	{

		PushLayer(new ExampleLayer());

	}
	~Sandbox() 
	{
		
	}

};

Dark::Application* Dark::CreateApplication() 
{
	return new Sandbox();
}