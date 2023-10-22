#include "SphereCollider.hpp"

namespace saintNecEngine
{

    namespace saintNecPhysics

    {
        SphereCollider::SphereCollider(Vector3 center, double radius)
        {
            _center = center;
            _radius = radius;
        }
    }
}