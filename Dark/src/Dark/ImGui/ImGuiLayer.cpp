#include <dpch.h>
#include "ImGuiLayer.h"

#include <Platform/OpenGL/ImGuiOpenGLRenderer.h>

#include "GLFW/glfw3.h"

#include "Dark/Application.h"

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
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

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
	}

}