#include "Dark.h"

class ExampleLayer : public Dark::Layer {

public:
	ExampleLayer()
		: Layer("ExampleLayer") {}

	virtual void OnUpdate() override {
		if (Dark::Input::IsKeyPressed(DK_KEY_TAB))
			DARK_CLIENT_TRACE("Tab Is Pressed!");
	}

	virtual void OnEvent(Dark::Event& event) {
		if (event.GetEventType() == Dark::EventType::KeyPressed) {
			Dark::KeyPressedEvent& e{ (Dark::KeyPressedEvent&)event };
			
			DARK_CLIENT_TRACE("{0}", (char)e.GetKeyCode());

		}
	}

};

class Sandbox : public Dark::Application {

public:
	Sandbox() {

		PushOverlay(new Dark::ImGuiLayer());

		PushLayer(new ExampleLayer());

	}
	~Sandbox() {
		
	}

};

Dark::Application* Dark::CreateApplication() {
	return new Sandbox();
}