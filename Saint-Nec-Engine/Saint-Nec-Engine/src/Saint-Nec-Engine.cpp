// Saint-Nec-Engine.cpp : définit le point d'entrée de l'application.
//
#include <src/architecture/Component.h>
#include <iostream>
#include <src/Physics/BoxCollider.hpp>
#include<src/Physics/SphereCollider.hpp>


using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	saintNecEngine::saintNecPhysics::BoxCollider cube{saintNecEngine::Vector3(0,0,0), 10, 10 ,10};
	saintNecEngine::saintNecPhysics::SphereCollider sphere{saintNecEngine::Vector3(0,0,0), 10};
	

	return 0;
}
