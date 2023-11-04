#include "SphereCollider.hpp"

namespace sne
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