#pragma once

#include "Dark/Core.h"
#include "Dark/Events/Event.h"

namespace Dark {

	//a forward decl for Layer object/class
	class Layer;

	class DARK_API LayerStack
	{

		std::vector<Layer*> m_Layers{};
		
		int m_LayerInsertIndex{0};

	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }

		inline const std::vector<Layer*>& GetLayers() { return m_Layers; }
	};

}