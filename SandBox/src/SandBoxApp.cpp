#include "Dark.h"

class Sandbox : public Dark::Application {

public:
	Sandbox() {

		PushOverlay(new Dark::ImGuiLayer());

	}
	~Sandbox() {
		
	}

};

Dark::Application* Dark::CreateApplication() {
	return new Sandbox();
}