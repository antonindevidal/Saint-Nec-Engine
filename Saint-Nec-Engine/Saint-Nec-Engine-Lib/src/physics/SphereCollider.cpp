#include "SphereCollider.hpp"

namespace sne
{

    namespace saintNecPhysics

    {
        SphereCollider::SphereCollider(glm::vec3 center, double radius) : _center(center), _radius(radius)
        {
        }

        const double SphereCollider::getRadius() const
        {
            return _radius;
        }
        
        const glm::vec3 &SphereCollider::getCenter() const
        {
            return _center;
        }
    }
}