#include "GameObject.hpp"

namespace sne
{
	GameObject::GameObject(): components(), model(1.0f), name("GameObject")
	{
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	GameObject::~GameObject()
	{
		for (Component* c : components)
		{
			delete c;
		}
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

	const std::vector<Component*> GameObject::getComponent() const
	{
		return components;
	}
	
	
	const glm::mat4& GameObject::getModel() const
	{
		return model;
	}
	void GameObject::setModel(const glm::mat4& newModel)
	{
		model = newModel;
	}

	void GameObject::translate(const glm::vec3& translation)
	{
		model = glm::translate(model, translation);
	}

	void GameObject::rotate(const float angle, const glm::vec3& axis)
	{
		model = glm::rotate(model, glm::radians(angle), axis);
	}

	const std::string& GameObject::getName() const
	{
		return name;
	}

	void GameObject::setName(const std::string& newName)
	{
		name = newName;
	}

}
