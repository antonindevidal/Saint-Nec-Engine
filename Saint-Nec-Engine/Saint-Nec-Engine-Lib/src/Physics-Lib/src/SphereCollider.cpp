#include "SphereCollider.hpp"


namespace Physics
{
    SphereCollider::SphereCollider(saintNecEngine::Vector3 center, double radius)
    {
        _center = center;
        _radius = radius;
    }
} 
