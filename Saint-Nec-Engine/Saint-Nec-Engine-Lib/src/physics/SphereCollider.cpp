#include "SphereCollider.hpp"

namespace sne::saintNecPhysics

{

    SphereCollider::SphereCollider(glm::vec3 center, double radius) : Collider(center), _radius(radius)
    {
    }

    const double SphereCollider::getRadius() const
    {
        return _radius;
    }

    bool SphereCollider::collide(const Collider *c) const
    {
        return c->collide(*this);
    }

    bool SphereCollider::collide(const SphereCollider &s) const
    {
        return hasSATCollision(*this, s);
        // Used like that because in the futur, template foncteur
    }
    bool SphereCollider::collide(const BoxCollider &b) const
    {
        return hasSATCollision(*this, b);
    }

    bool SphereCollider::intersection(const Collider *c, const glm::vec3 &axis) const
    {
        return c->intersection(*this, axis);
    }

    bool SphereCollider::intersection(const SphereCollider &s, const glm::vec3 &axis) const
    {
        return intersect(*this, s, axis);
    }

    bool SphereCollider::intersection(const BoxCollider &b, const glm::vec3 &axis) const
    {
        return intersect(*this, b, axis);
    }
}
