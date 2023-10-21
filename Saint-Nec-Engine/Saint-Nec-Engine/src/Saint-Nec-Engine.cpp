// Saint-Nec-Engine.cpp : définit le point d'entrée de l'application.
//
#include <src/architecture/Component.h>
#include <iostream>
#include <src/BoxCollider.hpp>
#include <src/SphereCollider.hpp>

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	Physics::BoxCollider cube{saintNecEngine::Vector3(0,0,0), 10, 10 ,10};
	Physics::SphereCollider sphere{saintNecEngine::Vector3(0,0,0), 10};
	

	return 0;
}
