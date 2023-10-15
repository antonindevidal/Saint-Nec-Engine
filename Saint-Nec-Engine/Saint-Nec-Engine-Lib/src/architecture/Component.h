#pragma once

namespace saintNecEngine
{
	class Component
	{

	public:
		Component() = default;
		~Component() = default;
		virtual void update() = 0;
		virtual void draw() const = 0;
	};
}