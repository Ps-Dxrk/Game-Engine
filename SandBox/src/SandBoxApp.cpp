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
	float m_CamSpeed{0.05f};
	float m_CamRotation{};
	float m_CamRotationSpeed{ 1.0f };

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

	void OnUpdate() override
	{

		//camera update
		if (Dark::Input::IsKeyPressed(DK_KEY_D)) m_CamPos.x += m_CamSpeed;
		if (Dark::Input::IsKeyPressed(DK_KEY_A)) m_CamPos.x -= m_CamSpeed;
		if (Dark::Input::IsKeyPressed(DK_KEY_W)) m_CamPos.y += m_CamSpeed;
		if (Dark::Input::IsKeyPressed(DK_KEY_S)) m_CamPos.y -= m_CamSpeed;

		if (Dark::Input::IsKeyPressed(DK_KEY_LEFT)) m_CamRotation += m_CamRotationSpeed;
		if (Dark::Input::IsKeyPressed(DK_KEY_RIGHT)) m_CamRotation -= m_CamRotationSpeed;
		//

		m_Camera.SetPosition(m_CamPos);
		m_Camera.SetRotation(m_CamRotation);

		Dark::RenderCommand::Clear(bg_clear_color);

		Dark::Renderer::BeginScene(m_Camera);

		Dark::Renderer::Submit(m_Shader, m_VertexArray);

		Dark::Renderer::Submit(m_Shader, m_SquareVA);

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