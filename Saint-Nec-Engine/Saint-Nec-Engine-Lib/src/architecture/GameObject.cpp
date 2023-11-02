#include "GameObject.h"

namespace sne
{
	GameObject::GameObject(): components(),model(1.0f)
	{
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	GameObject::~GameObject()
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
		component->parent = this;
		components.push_back(component);
	}
	
	
	const glm::mat4& GameObject::getModel()
	{
		return model;
	}
	void GameObject::setModel(const glm::mat4& newModel)
	{
		model = newModel;
	}


}