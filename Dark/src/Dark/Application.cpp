#include "dpch.h"

#include "Application.h"

#include "Dark/Events/ApplicationEvent.h"

namespace Dark {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance{ nullptr };


	Application::Application() {

		DARK_CORE_ASSERT(!s_Instance, "Application Already Exists");
		s_Instance = this;

		//creating window
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBackFn(BIND_EVENT_FN(Application::OnEvent));

	}

	Application::~Application() {

	}

	void Application::Run() {

		while(m_Running) {
			m_Window->OnUpdate();

			//layer update
			const auto& layers{ m_LayerStack.GetLayers() };
			if (!layers.empty()) {
				for (int i = 0; i < layers.size(); i++) {
					layers[i]->OnUpdate();
				}
			}
		}

	}

	//Event
	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e); //event dispatcher

		//Window closing event dispatch
		dispatcher.Dispatch<WindowCloseEvent>([this](const WindowCloseEvent& e) -> bool {
			m_Running = false;
			return true;
		});

		////layer event handling
		const auto& layers{ m_LayerStack.GetLayers() };
		if (!layers.empty()) {
			for (int i = layers.size() - 1; i >= 0; i--) {

				layers[i]->OnEvent(e);
				if (e.Handled()) break;

			}
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