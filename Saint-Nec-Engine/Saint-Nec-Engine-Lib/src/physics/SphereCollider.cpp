#include "SphereCollider.hpp"

namespace saintNecEngine
{

    namespace saintNecPhysics

    {
        SphereCollider::SphereCollider(Vector3 center, double radius) : _center(center), _radius(radius)
        {
        }

        const double SphereCollider::getRadius() const
        {
            return _radius;
        }
        
        const Vector3 &SphereCollider::getCenter() const
        {
            return _center;
        }
    }
}