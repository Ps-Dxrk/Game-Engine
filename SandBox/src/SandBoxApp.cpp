#include "Dark.h"

#include <imgui/imgui.h>

class ExampleLayer : public Dark::Layer
{
private:

	std::shared_ptr<Dark::VertexArray> m_VertexArray{};
	std::shared_ptr<Dark::VertexArray> m_SquareVA{};
	std::shared_ptr<Dark::Shader> m_Shader{};

	//bg color
	glm::vec4 bg_clear_color{};

	//camera
	Dark::OrthoGraphicCamera m_Camera;
	glm::vec3 m_CamPos{};
	float m_CamSpeed{5.0f};
	float m_CamRotation{};
	float m_CamRotationSpeed{ 90.0f };
public:
	ExampleLayer()
		: Layer("ExampleLayer"), m_Camera{ -3.2f, 3.2f, 1.8f, -1.8f }
	{

		m_VertexArray.reset(Dark::VertexArray::Create());

		float vertices[21]{
			0.25, -0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
			0.75, -0.5, 0.0, 0.0, 1.0, 0.0, 1.0,
			0.5, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0
		};

		std::shared_ptr<Dark::VertexBuffer> vertexBuffer{ Dark::VertexBuffer::Create(vertices, sizeof(vertices)) };

		Dark::BufferLayout layout
		{
			{"aPos", Dark::ShaderDataType::Float3},
			{"aColor", Dark::ShaderDataType::Float4}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3]{
			0, 1, 2
		};

		std::shared_ptr<Dark::IndexBuffer> indexBuffer{ Dark::IndexBuffer::Create(indices, 3) };
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//square
		m_SquareVA.reset(Dark::VertexArray::Create());

		float verticesSQ[28]{
			-0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
			0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 1.0,
			0.5, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0,
			-0.5, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0
		};

		std::shared_ptr<Dark::VertexBuffer> squareVB{ Dark::VertexBuffer::Create(verticesSQ, sizeof(verticesSQ)) };

		Dark::BufferLayout layoutSQ
		{
			{"aPos", Dark::ShaderDataType::Float3},
			{"aColor", Dark::ShaderDataType::Float4}
		};

		squareVB->SetLayout(layoutSQ);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t indicesSQ[6]{
			0, 1, 2, 2, 3, 0
		};

		std::shared_ptr<Dark::IndexBuffer> squareIB{ Dark::IndexBuffer::Create(indicesSQ, 6) };
		m_SquareVA->SetIndexBuffer(squareIB);

		m_Shader = std::make_unique<Dark::Shader>("D:\\DarkEngine\\Dark\\bin\\Debug-windows-x86_64\\Sandbox\\Shader\\vert.glsl", "D:\\DarkEngine\\Dark\\bin\\Debug-windows-x86_64\\Sandbox\\Shader\\frag.glsl");


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

		Dark::Renderer::Submit(m_Shader, m_VertexArray);

		const glm::mat4& scale{ glm::scale(glm::mat4{1.0f}, glm::vec3{0.3f}) };
		
		for (int y{}; y++ < 20; ) {
			for (int x{}; x++ < 20; ) {
				glm::vec3 pos{ x * 0.33f, y * 0.33f, 0.0f };
				const glm::mat4& transform{ glm::translate(glm::mat4{1.0f}, pos) * scale };
				Dark::Renderer::Submit(m_Shader, m_SquareVA, transform);
			}
		}

		Dark::Renderer::EndScene();
	}

	void OnEvent(Dark::Event& e) override
	{
	}

	void OnImGuiRender() override
	{
		ImGui::Begin(m_Name.c_str());
			ImGui::ColorPicker4("BgClearColor", &bg_clear_color.x);
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