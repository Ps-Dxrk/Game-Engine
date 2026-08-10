#include <dpch.h>
#include "ImGuiLayer.h"

#include <Platform/OpenGL/ImGuiOpenGLRenderer.h>

#include "Dark/Application.h"

#include "Dark/Input.h"

//TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Dark {

	ImGuiLayer::ImGuiLayer() 
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach() 
	{
		//Initial ImGui Set up On Attach
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io{ ImGui::GetIO() };
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 440");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io{ ImGui::GetIO() };
		Application& app{ Application::Get() };
		io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

		//new frame
		ImGui::NewFrame();
		ImGui_ImplOpenGL3_NewFrame();

		//delta time
		float time{ static_cast<float>(glfwGetTime()) };
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;
		/********/

		//demo window
		static bool show_demo{ true };
		ImGui::ShowDemoWindow(&show_demo);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher{ e };

		dispatcher.Dispatch < MouseButtonPressedEvent >     (DARK_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch <MouseButtonReleasedEvent >     (DARK_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch <     MouseMovedEvent     >     (DARK_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch <    MouseScrolledEvent   >     (DARK_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch <     KeyPressedEvent     >     (DARK_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch <     KeyReleasedEvent    >     (DARK_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch <    WindowResizeEvent    >     (DARK_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
		dispatcher.Dispatch <      KeyTypedEvent      >     (DARK_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
	}

	//specific event fns
	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{

		ImGuiIO& io{ ImGui::GetIO() };
		io.AddMouseButtonEvent(e.GetMouseButton(), true);

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io{ ImGui::GetIO() };
		io.AddMouseButtonEvent(e.GetMouseButton(), false);

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{

		ImGuiIO& io{ ImGui::GetIO() };
		io.AddMousePosEvent(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io{ ImGui::GetIO() };
		io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io{ ImGui::GetIO() };

		ImGuiKey imgui_key{ ImGuiLayer::DKKeyToImGuiKey(e.GetKeyCode()) };
		io.AddKeyEvent(imgui_key, true);

		ImGuiKey imgui_mod_key{ ImGuiLayer::DKKeyToImGuiModKey(e.GetKeyCode()) };
		io.AddKeyEvent(imgui_mod_key, true);

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io{ ImGui::GetIO() };

		ImGuiKey imgui_key{ ImGuiLayer::DKKeyToImGuiKey(e.GetKeyCode()) };
		io.AddKeyEvent(imgui_key, false);

		ImGuiKey imgui_mod_key{ ImGuiLayer::DKKeyToImGuiModKey(e.GetKeyCode()) };
		io.AddKeyEvent(imgui_mod_key, false);

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{

		ImGuiIO& io{ ImGui::GetIO() };
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io{ ImGui::GetIO() };

		int keycode{ e.GetKeyCode() };
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);
		
		return false;
	}

	//manual key mapping from glw to imgui
	ImGuiKey ImGuiLayer::DKKeyToImGuiKey(int key)
	{
		switch (key)
		{
			case DK_KEY_TAB:         return ImGuiKey_Tab;
			case DK_KEY_LEFT:        return ImGuiKey_LeftArrow;
			case DK_KEY_RIGHT:       return ImGuiKey_RightArrow;
			case DK_KEY_UP:          return ImGuiKey_UpArrow;
			case DK_KEY_DOWN:        return ImGuiKey_DownArrow;
			case DK_KEY_PAGE_UP:     return ImGuiKey_PageUp;
			case DK_KEY_PAGE_DOWN:   return ImGuiKey_PageDown;
			case DK_KEY_HOME:        return ImGuiKey_Home;
			case DK_KEY_END:         return ImGuiKey_End;
			case DK_KEY_INSERT:      return ImGuiKey_Insert;
			case DK_KEY_DELETE:      return ImGuiKey_Delete;
			case DK_KEY_BACKSPACE:   return ImGuiKey_Backspace;
			case DK_KEY_SPACE:       return ImGuiKey_Space;
			case DK_KEY_ENTER:       return ImGuiKey_Enter;
			case DK_KEY_ESCAPE:      return ImGuiKey_Escape;

			case DK_KEY_APOSTROPHE:  return ImGuiKey_Apostrophe;
			case DK_KEY_COMMA:       return ImGuiKey_Comma;
			case DK_KEY_MINUS:       return ImGuiKey_Minus;
			case DK_KEY_PERIOD:      return ImGuiKey_Period;
			case DK_KEY_SLASH:       return ImGuiKey_Slash;
			case DK_KEY_SEMICOLON:   return ImGuiKey_Semicolon;
			case DK_KEY_EQUAL:       return ImGuiKey_Equal;
			case DK_KEY_LEFT_BRACKET:return ImGuiKey_LeftBracket;
			case DK_KEY_BACKSLASH:   return ImGuiKey_Backslash;
			case DK_KEY_RIGHT_BRACKET:return ImGuiKey_RightBracket;
			case DK_KEY_GRAVE_ACCENT:return ImGuiKey_GraveAccent;

			case DK_KEY_CAPS_LOCK:   return ImGuiKey_CapsLock;
			case DK_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
			case DK_KEY_NUM_LOCK:    return ImGuiKey_NumLock;
			case DK_KEY_PRINT_SCREEN:return ImGuiKey_PrintScreen;
			case DK_KEY_PAUSE:       return ImGuiKey_Pause;

			case DK_KEY_LEFT_SHIFT:   return ImGuiKey_LeftShift;
			case DK_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
			case DK_KEY_LEFT_ALT:     return ImGuiKey_LeftAlt;
			case DK_KEY_LEFT_SUPER:   return ImGuiKey_LeftSuper;

			case DK_KEY_RIGHT_SHIFT:   return ImGuiKey_RightShift;
			case DK_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
			case DK_KEY_RIGHT_ALT:     return ImGuiKey_RightAlt;
			case DK_KEY_RIGHT_SUPER:   return ImGuiKey_RightSuper;

			case DK_KEY_F1:  return ImGuiKey_F1;
			case DK_KEY_F2:  return ImGuiKey_F2;
			case DK_KEY_F3:  return ImGuiKey_F3;
			case DK_KEY_F4:  return ImGuiKey_F4;
			case DK_KEY_F5:  return ImGuiKey_F5;
			case DK_KEY_F6:  return ImGuiKey_F6;
			case DK_KEY_F7:  return ImGuiKey_F7;
			case DK_KEY_F8:  return ImGuiKey_F8;
			case DK_KEY_F9:  return ImGuiKey_F9;
			case DK_KEY_F10: return ImGuiKey_F10;
			case DK_KEY_F11: return ImGuiKey_F11;
			case DK_KEY_F12: return ImGuiKey_F12;

			default:
				break;
		}

		// Numbers
		if (key >= DK_KEY_0 && key <= DK_KEY_9)
			return static_cast<ImGuiKey>(
				ImGuiKey_0 + (key - DK_KEY_0)
				);

		// Letters
		if (key >= DK_KEY_A && key <= DK_KEY_Z)
			return static_cast<ImGuiKey>(
				ImGuiKey_A + (key - DK_KEY_A)
				);

		return ImGuiKey_None;
	}

	ImGuiKey ImGuiLayer::DKKeyToImGuiModKey(int key) {

		if (key == DK_KEY_LEFT_ALT     || key == DK_KEY_RIGHT_ALT    )		return    ImGuiMod_Alt;
		if (key == DK_KEY_LEFT_CONTROL || key == DK_KEY_RIGHT_CONTROL)      return   ImGuiMod_Ctrl;
		if (key == DK_KEY_LEFT_SHIFT   || key == DK_KEY_RIGHT_SHIFT  )		return  ImGuiMod_Shift;
		if (key == DK_KEY_LEFT_SUPER   || key == DK_KEY_RIGHT_SUPER  )  	return  ImGuiMod_Super;

		return ImGuiMod_None;
	}

}