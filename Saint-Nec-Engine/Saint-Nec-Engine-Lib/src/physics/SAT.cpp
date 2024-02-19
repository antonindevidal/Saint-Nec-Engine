#include "SAT.hpp"
#include <algorithm>
#include "util.hpp"
namespace sne::physics
{

    std::vector<glm::vec3> operator+(std::vector<glm::vec3> v1, const std::vector<glm::vec3> &v2)
    {
        for (auto elt : v2)
            v1.push_back(elt);
        
        return v1;
    }

    bool hasSATCollision(const BoxCollider &boxe1, const BoxCollider &boxe2)
    {
        // Each BoxCollider has 3 normal axis
        std::vector<glm::vec3> v = boxe1.getAxis() + boxe2.getAxis();

        // SAT
        // Theoreme:
        // If there is any gap (one disjoint) then there is no collision
        // Otherwise, if we didn't find any gap then it collides
        return !std::any_of(std::begin(v), std::end(v), [&](glm::vec3& axis)
        {
            return !intersect(boxe1, boxe2, axis); // if true => we find a gap
        });
    }

    bool hasSATCollision(const SphereCollider &sphere1, const SphereCollider &sphere2)
    {
        // Evaluate the distance between the 2 centers
        double distance = norm(sphere1.getCenter() - sphere2.getCenter());
        return distance <= (sphere1.getRadius() + sphere2.getRadius());
    }

    bool hasSATCollision(const BoxCollider &boxe, const SphereCollider &sphere)
    {
        using glm::dot;
        // Evaluate the distance between the 2 centers
        std::vector<glm::vec3> v = boxe.getAxis();

        // SAT
        for (glm::vec3 axis : v)
        {
            // We check a if a gap exist on each axis
            float boxe_min = dot(axis, boxe[0]),
                   boxe_max = boxe_min,
                   sphere_min = dot(axis, sphere.getCenter()) - sphere.getRadius(),
                   sphere_max = dot(axis, sphere.getCenter()) + sphere.getRadius();

            for (int i = 1; i < boxe.getNbPoints(); i++)
            {
                float boxe_projection = dot(axis, boxe[i]);

                boxe_min = (boxe_min < boxe_projection) ? boxe_min : boxe_projection;
                boxe_max = (boxe_max > boxe_projection) ? boxe_max : boxe_projection;
            }

            // Theoreme:
            // If there is any gap (one disjoint) then there is no collision
            if (areDisjoint(boxe_min, boxe_max, sphere_min, sphere_max))
            { // We have a gap, there is no collision
                return false;
            }
        }

        return true;
    }

    bool hasSATCollision(const SphereCollider &sphere, const BoxCollider &boxe)
    {
        return hasSATCollision(boxe, sphere);
    }
}
