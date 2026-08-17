#pragma once

namespace Dark {

	class DARK_API Timer {

		static std::chrono::time_point<std::chrono::high_resolution_clock> s_StartTimePoint;

	public:
		static void Init();

		static float GetElapsedTime();

	};

}