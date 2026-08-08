#pragma once

#include "Dark/Core.h"
#include "Dark/Events/Event.h"

namespace Dark {
	class DARK_API Layer
	{
	protected:

		std::string m_Name{};

	public:
		Layer(const std::string& u_LayerName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetLayerName() { return m_Name; }
	};

}