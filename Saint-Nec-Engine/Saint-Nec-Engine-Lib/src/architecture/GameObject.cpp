#include "GameObject.h"


namespace sne
{
	GameObject::GameObject()
	{

	}


	void GameObject::update()
	{
		for (Component *c : components)
		{
			c->update();
		}
	}

	void GameObject::draw() const
	{
		for (Component* c : components)
		{
			c->draw();
		}
	}

	void GameObject::addComponent(Component* component)
	{
		components.push_back(component);
	}

}