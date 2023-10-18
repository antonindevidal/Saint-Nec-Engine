#include "Forme.hpp"

namespace saintNecEngine
{
    Forme::Forme(Vector3 &center, Vector3 &rotation) : GameObject(center, rotation)
    {
    }

    void Forme::addPoint(Vector3 &p)
    {
        Points.push_back(p);
    }

    void Forme::addPoint(double x, double y, double z)
    {
        Points.push_back(Vector3(x, y, z));
    }

    Square::Square(Vector3 &center, Vector3 &rotation, double size) : Forme(center, rotation)
    {
        // No calcul with angle for now
        // For the moment we considere the square only on axis x and y
        Points.push_back(Vector3{center[0] - size / 2, center[1] - size / 2, center[2]});
        Points.push_back(Vector3{center[0] + size / 2, center[1] + size / 2, center[2]});
        Points.push_back(Vector3{center[0] - size / 2, center[1] + size / 2, center[2]});
        Points.push_back(Vector3{center[0] + size / 2, center[1] - size / 2, center[2]});
    }
}