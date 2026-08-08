#pragma once

#include "Dark/Core.h"
#include "Dark/Events/Event.h"

namespace Dark {

	//a forward decl for Layer object/class
	class Layer;

	class DARK_API LayerStack
	{

		std::vector<Layer*> m_Layers{};
		
		int m_LayerIndex{0};

	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		inline const std::vector<Layer*>& GetLayers() { return m_Layers; }
	};

}