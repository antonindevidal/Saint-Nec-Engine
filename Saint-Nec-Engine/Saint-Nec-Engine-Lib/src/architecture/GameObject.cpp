#include "GameObject.h"


namespace sne
{
	GameObject::GameObject(): components(),model(1.0f)
	{

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
		components.push_back(component);
	}
	/*
	void GameObject::addComponent(graphics::Shader* component)
	{
		shader = component;
		shader->setMat4("projection", SceneManager::getInstance()->getCurrentScene().getProjection());
		shader->setMat4("view", SceneManager::getInstance()->getCurrentScene().getView());
	}*/

}