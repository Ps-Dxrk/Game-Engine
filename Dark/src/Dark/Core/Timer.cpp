#include "dpch.h"
#include "Timer.h"

namespace Dark {

	auto Timer::s_StartTimePoint = std::chrono::high_resolution_clock::now();

	void Timer::Init() {
		s_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	float Timer::GetElapsedTime() {
		std::chrono::time_point<std::chrono::high_resolution_clock> cur_time{ std::chrono::high_resolution_clock::now() };
		std::chrono::duration<float, std::chrono::seconds::period> elapsed_time{ cur_time - s_StartTimePoint };
		return elapsed_time.count();
	}

}