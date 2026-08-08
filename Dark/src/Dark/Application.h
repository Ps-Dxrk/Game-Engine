#pragma once

#include "Core.h"

#include "Layer.h"
#include "LayerStack.h"

#include "Events/Event.h"


namespace Dark {

	class Window;

	class WindowCloseEvent;

	class DARK_API Application {

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		//layer stack
		LayerStack m_LayerStack;

	public:

		Application();
		virtual ~Application();

		void Run();

		//Event
		void OnEvent(Event& e);

		//layer stack
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	};

	//To be defined in CLIENT!
	Application* CreateApplication();

}