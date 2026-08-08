#pragma once

#include "Dark/Window.h"

struct GLFWwindow;

namespace Dark {

	class WindowsWindow : public Window
	{
	private:
		struct WindowData {
			std::string title;
			uint32_t width, height;
			bool isVsync;

			EventCallBackFn CallBackFn;
		};

		GLFWwindow* m_Window;
		WindowData m_Data;

	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();

		void OnUpdate() override;

		//win props
		inline uint32_t GetWidth() const override { return m_Data.width; }
		inline uint32_t GetHeight() const override { return m_Data.height; }
		inline const std::string& GetTitle() const override { return m_Data.title; }

		//vsync
		void SetVsync(bool val) override;
		bool IsVsync() const override;

		//event call back
		inline void SetEventCallBackFn(const EventCallBackFn& callBackFn) override { m_Data.CallBackFn = callBackFn; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
	};

}

