#pragma once

namespace saintNecEngine
{
	class Component
	{

	public:
		Component() = default;
		virtual~Component() = 0;

		virtual void update() {};
		virtual void draw() const {};
	};
}