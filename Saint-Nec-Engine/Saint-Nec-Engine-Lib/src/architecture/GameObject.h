#pragma once
#include <vector>
#include "Component.h"
#include <iostream>
namespace saintNecEngine
{
	class Vector3
	{ // OpenGL like + permet la fonction d'affichage
		double vect[3];

	public:
		Vector3() : Vector3(0, 0, 0) {} // Pas de 'point par default' ?
		Vector3(double x, double y, double z)
		{
			vect[0] = x;
			vect[1] = y;
			vect[2] = z;
		}
		double &operator[](int i)
		{
			return vect[i];
		}

		const double &operator[](int i) const
		{
			return vect[i];
		}
	};

	// En général je garde celle là dans le hpp, dis moi si tu n'aimes pas
	std::ostream &operator<<(std::ostream &oss, const Vector3 &v)
	{
		oss << "(x=" << v[0] << ", y=" << v[1] << ", z=" << v[2] << ")";
		return oss;
	}

	class GameObject
	{
		Vector3 _center; // Are you ok to rename it ?
		Vector3 _rotation;
		// std::vector<Component *> components;

	public:
		GameObject() = default;							// Pas très chaud de garder ça
		GameObject(Vector3 &center, Vector3 &rotation); // Les points ne sont pas const étant donné qu'ils sont déstinés à se mouvoir, j'ajouterai le const 6 double plus tard
		virtual ~GameObject() = default;
		virtual void update(){};	  // A mettre en abstract plus tard
		virtual void draw() const {}; // A mettre en abstract plus tard
	};
}