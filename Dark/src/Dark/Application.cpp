#include "dpch.h"

#include "Application.h"

#include "Dark/Events/ApplicationEvent.h"

#include "Dark/Input.h"

#include "Dark/Renderer/Shader.h"
#include "Dark/Renderer/Buffer.h"
#include "Dark/Renderer/VertexArray.h"

#include "Dark/Renderer/Renderer.h"

namespace Dark {
	Application* Application::s_Instance{ nullptr };

	Application::Application()
		: m_Camera{ -3.2f, 3.2f, 1.8f, -1.8f }
	{

		DARK_CORE_ASSERT(!s_Instance, "Application Already Exists");
		s_Instance = this;

		//creating window
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBackFn(DARK_BIND_EVENT_FN(Application::OnEvent));

		//creating teh imgui layer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[21]{
			0.25, -0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
			0.75, -0.5, 0.0, 0.0, 1.0, 0.0, 1.0,
			0.5, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0
		};

		std::shared_ptr<VertexBuffer> vertexBuffer{ VertexBuffer::Create(vertices, sizeof(vertices)) };

		BufferLayout layout
		{
			{"aPos", ShaderDataType::Float3},
			{"aColor", ShaderDataType::Float4}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3]{
			0, 1, 2
		};

		std::shared_ptr<IndexBuffer> indexBuffer{ IndexBuffer::Create(indices, 3) };
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//square
		m_SquareVA.reset(VertexArray::Create());

		float verticesSQ[28]{
			-0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
			0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 1.0,
			0.5, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0,
			-0.5, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0
		};

		std::shared_ptr<VertexBuffer> squareVB{ VertexBuffer::Create(verticesSQ, sizeof(verticesSQ)) };

		BufferLayout layoutSQ
		{
			{"aPos", ShaderDataType::Float3},
			{"aColor", ShaderDataType::Float4}
		};

		squareVB->SetLayout(layoutSQ);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t indicesSQ[6]{
			0, 1, 2, 2, 3, 0
		};

		std::shared_ptr<IndexBuffer> squareIB{ IndexBuffer::Create(indicesSQ, 6) };
		m_SquareVA->SetIndexBuffer(squareIB);

		m_Shader = std::make_unique<Shader>("D:\\DarkEngine\\Dark\\bin\\Debug-windows-x86_64\\Sandbox\\Shader\\vert.glsl", "D:\\DarkEngine\\Dark\\bin\\Debug-windows-x86_64\\Sandbox\\Shader\\frag.glsl");

		//camera stuff
		m_Camera.SetRotation(45.0f);
		m_Camera.SetPosition({ 0.0f, 0.0f, 0.0f });
	}

	Application::~Application() {

	}

	void Application::Run() {

		while(m_Running) {

			RenderCommand::Clear({ 0.0f, 0.5f, 0.5f, 1.0f });

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_Shader, m_VertexArray);

			Renderer::Submit(m_Shader, m_SquareVA);

			Renderer::EndScene();
	
			//layer update
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			//imgui rendering for the layers
			m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
			m_ImGuiLayer->End();


			//window update
			m_Window->OnUpdate();
		}

	}

	//Event
	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher{ e }; //event dispatcher

		//Window closing event dispatch
		dispatcher.Dispatch<WindowCloseEvent>([this](const WindowCloseEvent& e) -> bool {
			m_Running = false;
			return true;
		});

		////layer event handling
		for (auto it{ m_LayerStack.rbegin() }; it != m_LayerStack.rend(); it++) {
			(*it)->OnEvent(e);
			if (e.Handled()) break;
		}

	}

	//layer stack
	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	//TODO: Pop wrappers for the LayerStack

}