#pragma once

namespace Dark {

	enum class RendererAPI {
		None = 0,
		OpenGL = 1,
		Direct3D = 2,
		Vulkan = 3,
		Metal = 4
	};

	class Renderer {

	private:
		static RendererAPI s_RendererAPI;

	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
		inline static void SetAPI(RendererAPI api) { s_RendererAPI = api; }

	};

}