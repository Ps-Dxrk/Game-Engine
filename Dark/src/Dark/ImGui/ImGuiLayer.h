#pragma once

#include <Dark/Layer.h>

#include <Dark/Events/ApplicationEvent.h>
#include <Dark/Events/KeyEvent.h>
#include <Dark/Events/MouseEvent.h>

enum ImGuiKey;

namespace Dark {

	class DARK_API ImGuiLayer : public Layer {

	private:

		float m_Time{};
	
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

	//private functione
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		//manual key mapping from glw to imgui
		static ImGuiKey glfwKeyToImGuiKey(int key);
		static ImGuiKey glfwKeyToImGuiModKey(int key);

	};

}