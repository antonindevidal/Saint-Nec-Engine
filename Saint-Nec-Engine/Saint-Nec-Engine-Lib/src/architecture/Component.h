#pragma once




namespace sne
{
	class GameObject;
	
	
	class Component
	{
	public:
		GameObject* parent;

	public:
		Component() = default;
		virtual ~Component() = 0;

		virtual void update() {};
		virtual void draw() const {};
	};
}