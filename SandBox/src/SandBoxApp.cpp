#include "Dark.h"

class ExampleLayer : public Dark::Layer {

public:

	ExampleLayer() : Layer("Example") {

	}

	void OnEvent(Dark::Event& e) override{
		//DARK_CLIENT_INFO(e);
	}
	void OnUpdate() override {
		//DARK_CLIENT_INFO("Example Layer: Update");
	}

};

class Sandbox : public Dark::Application {

public:
	Sandbox() {

		PushLayer(new ExampleLayer());

	}
	~Sandbox() {
	
	}

};

Dark::Application* Dark::CreateApplication() {
	return new Sandbox();
}