#include "util.hpp"
// #include "../architecture/util.hpp"

namespace sne::physics
{
    glm::vec3 getNormal(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return glm::cross(v1, v2);
    }

    bool areDisjoint(double x1_min, double x1_max, double x2_min, double x2_max)
    {
        // Returns true if: [x1_min ; x1_max] ∩ [x2_min; x2_max] = ∅
        return x1_max < x2_min || x2_max < x1_min;
    }

    double dot(const glm::vec3 v1, const glm::vec3 v2)
    {
        // If one of the vector norm is 1 then it's a simple projection
        return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    }

    bool intersect(const BoxCollider &boxe1, const BoxCollider &boxe2, const glm::vec3 &axis)
    {
        double boxe1_min = dot(axis, boxe1[0]),
               boxe1_max = boxe1_min,
               boxe2_min = dot(axis, boxe2[0]),
               boxe2_max = boxe2_min;

        for (int i = 1; i < boxe1.getNbPoints(); i++)
        {
            double boxe1_projection = dot(axis, boxe1[i]),
                   boxe2_projection = dot(axis, boxe2[i]);

            boxe1_min = (boxe1_min < boxe1_projection) ? boxe1_min : boxe1_projection;
            boxe1_max = (boxe1_max > boxe1_projection) ? boxe1_max : boxe1_projection;
            boxe2_min = (boxe2_min < boxe2_projection) ? boxe2_min : boxe2_projection;
            boxe2_max = (boxe2_max > boxe2_projection) ? boxe2_max : boxe2_projection;
        }

        return !areDisjoint(boxe1_min, boxe1_max, boxe2_min, boxe2_max);
    }

    bool intersect(const SphereCollider &sphere1, const SphereCollider &sphere2, const glm::vec3 &axis)
    {
        (void)axis;
        double distance = norm(sphere1.getCenter() - sphere2.getCenter());

        return distance > (sphere1.getRadius() + sphere2.getRadius());
    }

    bool intersect(const SphereCollider &sphere, const BoxCollider &boxe, const glm::vec3 &axis)
    {
        double boxe_min = dot(axis, boxe[0]),
               boxe_max = boxe_min,
               sphere_min = dot(axis, sphere.getCenter()) - sphere.getRadius(),
               sphere_max = dot(axis, sphere.getCenter()) + sphere.getRadius();

        for (int i = 1; i < boxe.getNbPoints(); i++)
        {
            double boxe_projection = dot(axis, boxe[i]);

            boxe_min = (boxe_min < boxe_projection) ? boxe_min : boxe_projection;
            boxe_max = (boxe_max > boxe_projection) ? boxe_max : boxe_projection;
        }

        return !areDisjoint(boxe_min, boxe_max, sphere_min, sphere_max);
    }

    bool intersect(const BoxCollider &boxe, const SphereCollider &sphere, const glm::vec3 &axis)
    {
        return intersect(sphere, boxe, axis);
    }
}