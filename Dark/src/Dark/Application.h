#pragma once

#include "Core.h"

#include "Dark/Layer.h"
#include "Dark/LayerStack.h"

#include "Dark/Events/Event.h"

#include "Dark/Window.h"

#include "Dark/ImGui/ImGuiLayer.h"

namespace Dark {

	class WindowCloseEvent;

	class DARK_API Application {

		//static instance of the application to access it from anywhere
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		//layer stack
		LayerStack m_LayerStack;

		//imgui layer
		ImGuiLayer* m_ImGuiLayer;

		//opengl stuff
		uint32_t m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	public:

		Application();
		virtual ~Application();

		void Run();

		//Event
		void OnEvent(Event& e);

		//layer stack
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		//function to get the window
		inline Window& GetWindow() { return *m_Window; }

		//accessing application from anywhere
		inline static Application& Get() { return *s_Instance; }
	};

	//To be defined in CLIENT!
	Application* CreateApplication();

}