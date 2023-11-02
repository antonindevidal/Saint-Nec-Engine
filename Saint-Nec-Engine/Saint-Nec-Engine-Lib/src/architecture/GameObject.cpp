#include "GameObject.h"
#include <iostream>

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
		/*
		if (shader != NULL)
		{
			shader->setMat4("view", SceneManager::getInstance()->getCurrentScene().getView());
		}*/
		for (Component *c : components)
		{
			c->update();
		}
	}

	void GameObject::draw() const
	{
		/*
		if (shader != NULL)
		{
			shader->use();
		}*/
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
	
	
	glm::mat4 GameObject::getModel()
	{
		return model;
	}

}