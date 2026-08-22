#pragma once

namespace Dark {

	class DARK_API Texture {

	public:
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void Bind(uint8_t t_Slot = 0) const = 0;
		virtual void UnBind() const = 0;

	};

	class Texture2D : public Texture {

	public:
		static Ref<Texture2D> Create(const std::string& filePath);

	};

}