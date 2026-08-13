#include "dpch.h"

#include "Application.h"

#include "Dark/Events/ApplicationEvent.h"

#include <glad/glad.h>

#include "Dark/Input.h"

#include "Dark/Renderer/Shader.h"

namespace Dark {
	Application* Application::s_Instance{ nullptr };


	Application::Application() {

		DARK_CORE_ASSERT(!s_Instance, "Application Already Exists");
		s_Instance = this;

		//creating window
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBackFn(DARK_BIND_EVENT_FN(Application::OnEvent));

		//creating teh imgui layer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		float vertices[9]{
			-0.5, -0.5, 0.0,
			0.5, -0.5, 0.0,
			0.0, 0.5, 0.0
		};

		uint32_t indices[3]{
			0, 1, 2
		};

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		m_Shader = std::make_unique<Shader>("D:\\DarkEngine\\Dark\\bin\\Debug-windows-x86_64\\Sandbox\\Shader\\vert.glsl", "D:\\DarkEngine\\Dark\\bin\\Debug-windows-x86_64\\Sandbox\\Shader\\frag.glsl");

	}

	Application::~Application() {

	}

	void Application::Run() {

		while(m_Running) {

			glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
			m_Shader->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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