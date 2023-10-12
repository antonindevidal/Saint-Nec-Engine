#pragma once
class Component // Abstraite ? On manipule forcément une sous classe
{

public:
	Component() = default;
	~Component() = default;
	virtual void update() = 0;
	virtual void draw() const = 0;
};

// Si pas de réel besoin, ajouter les classes filles ici ?
class Texture : public Component
{
};

class Rigidbody: public Component
{
};