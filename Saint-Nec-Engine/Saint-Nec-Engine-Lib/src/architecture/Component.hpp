#pragma once

namespace saintNecEngine
{
	class Component
	{
	protected:
		Component() = default;

	public:
		~Component() = default;
		virtual void update(){};
		virtual void draw() const {};
	};
}