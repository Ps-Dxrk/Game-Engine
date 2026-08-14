#include "dpch.h"

#include "Application.h"

#include "Dark/Events/ApplicationEvent.h"

#include <glad/glad.h>

#include "Dark/Input.h"

#include "Dark/Renderer/Shader.h"
#include "Dark/Renderer/Buffer.h"

namespace Dark {
	Application* Application::s_Instance{ nullptr };

	//temporary, will be updated
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Uint:     return GL_UNSIGNED_INT;
			case ShaderDataType::Uint2:    return GL_UNSIGNED_INT;
			case ShaderDataType::Uint3:    return GL_UNSIGNED_INT;
			case ShaderDataType::Uint4:    return GL_UNSIGNED_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		DARK_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application() {

		DARK_CORE_ASSERT(!s_Instance, "Application Already Exists");
		s_Instance = this;

		//creating window
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBackFn(DARK_BIND_EVENT_FN(Application::OnEvent));

		//creating teh imgui layer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		float vertices[21]{
			-0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
			0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 1.0,
			0.0, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0
		};

		uint32_t indices[3]{
			0, 1, 2
		};

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->Bind();

		{
			BufferLayout layout
			{
				{"aPos", ShaderDataType::Float3},
				{"aColor", ShaderDataType::Float4}
			};

			m_VertexBuffer->SetLayout(layout);
		}
		
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_IndexBuffer->Bind();

		uint32_t idx{};
		for (const auto& elements : m_VertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer(idx, 
				elements.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(elements.type),
				elements.Normalized ? GL_TRUE : GL_FALSE,
				m_VertexBuffer->GetLayout().GetStride(),
				(const void*)elements.offset);
			idx++;
		}

		m_Shader = std::make_unique<Shader>("D:\\DarkEngine\\Dark\\bin\\Debug-windows-x86_64\\Sandbox\\Shader\\vert.glsl", "D:\\DarkEngine\\Dark\\bin\\Debug-windows-x86_64\\Sandbox\\Shader\\frag.glsl");

	}

	Application::~Application() {

	}

	void Application::Run() {

		while(m_Running) {

			glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);
			m_IndexBuffer->Bind();
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