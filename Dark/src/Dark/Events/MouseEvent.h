#pragma once

#include "Event.h"

namespace Dark {

	class DARK_API MouseMovedEvent : public Event {

		float m_MouseX{}, m_MouseY{};

	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {
		}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream ss;

			ss << "MouseMoved: " << m_MouseX << ", " << m_MouseY;

			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	};

	class DARK_API MouseScrolledEvent : public Event {

		float m_XOffset{}, m_YOffset{};

	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {

		}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {
			std::stringstream ss;

			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;

			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	};

	//Can't Create a Constructor on its own, must be inherited by the ButtonPress event and release event classes
	class DARK_API MouseButtonEvent : public Event {
	protected:

		int m_Button{ -1 };

		MouseButtonEvent(int b)
			: m_Button(b) {

		}

	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	};

	class DARK_API MouseButtonPressedEvent : public MouseButtonEvent {

	public:
		MouseButtonPressedEvent(int b)
			: MouseButtonEvent(b) {}

		EVENT_CLASS_TYPE(MouseButtonPressed);

		std::string ToString() const override {
			std::stringstream ss;

			ss << "MouseButtonPressedEvent: " << m_Button;

			return ss.str();
		}

	};

	class DARK_API MouseButtonReleasedEvent : public MouseButtonEvent {

	public:
		MouseButtonReleasedEvent(int b)
			: MouseButtonEvent(b) {}

		EVENT_CLASS_TYPE(MouseButtonReleased);

		std::string ToString() const override {
			std::stringstream ss;

			ss << "MouseButtonReleaseEvent: " << m_Button;

			return ss.str();
		}

	};
}