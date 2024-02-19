#include "SphereCollider.hpp"
#include "SAT.hpp"
#include "util.hpp"

namespace sne::physics

{

    SphereCollider::SphereCollider(glm::vec3 center, float radius) : Collider(center), _radius(radius)
    {
    }

    const float SphereCollider::getRadius() const
    {
        return _radius;
    }

    bool SphereCollider::collide(const Collider *c, glm::vec3& normal) const
    {
        return c->collide(*this, normal);
    }

    bool SphereCollider::collide(const SphereCollider &s, glm::vec3& normal) const
    {
        return gjk(*this, s, normal);
        // Used like that because in the futur, template foncteur
    }
    bool SphereCollider::collide(const BoxCollider &b, glm::vec3& normal) const
    {
        return gjk(*this, b, normal);
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

    float SphereCollider::getMin(const glm::vec3 &axis) const
    {
        return dot(axis, _center) - _radius;
    }

    float SphereCollider::getMax(const glm::vec3 &axis) const
    {
        return dot(axis, _center) + _radius;
    }

    glm::vec3 SphereCollider::farthestPoint(const glm::vec3 &axis) const
    {

        // Normalize axis
        glm::vec3 directionNormalized = glm::normalize(axis);

        // Incrementing with _radius
        glm::vec3 surfacePoint = _center + (float)_radius * directionNormalized;

        return surfacePoint;
    }
}
