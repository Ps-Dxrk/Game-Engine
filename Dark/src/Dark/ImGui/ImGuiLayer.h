#pragma once

#include <Dark/Core.h>
#include <Dark/Layer.h>

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

	};

}