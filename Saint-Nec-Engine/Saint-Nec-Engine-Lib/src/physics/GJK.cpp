#include "GJK.hpp"
#include <algorithm>
#include "util.hpp"
#include "Minkowski.hpp"

namespace sne::physics
{
    bool hasGJKCollision(const BoxCollider &boxe1, const BoxCollider &boxe2)
    {
        std::vector<Minkowski> minkowskiSum;

        for(auto &point: boxe1.getPoints())
            for(auto &point2: boxe2.getPoints())
                minkowskiSum.push_back(Minkowski{point, point2, false});
        
        

        return true;
    }

    bool hasGJKCollision(const SphereCollider &sphere1, const SphereCollider &sphere2)
    {
        // Evaluate the distance between the 2 centers
        double distance = norm(sphere1.getCenter() - sphere2.getCenter());
        return distance <= (sphere1.getRadius() + sphere2.getRadius());
    }

    // bool hasSATCollision(const BoxCollider &boxe, const SphereCollider &sphere)
    // {
    //     // Evaluate the distance between the 2 centers
    //     std::vector<glm::vec3> v = boxe.getAxis();

    //     // SAT
    //     for (glm::vec3 axis : v)
    //     {
    //         // We check a if a gap exist on each axis
    //         double boxe_min = dot(axis, boxe[0]),
    //                boxe_max = boxe_min,
    //                sphere_min = dot(axis, sphere.getCenter()) - sphere.getRadius(),
    //                sphere_max = dot(axis, sphere.getCenter()) + sphere.getRadius();

    //         for (int i = 1; i < boxe.getNbPoints(); i++)
    //         {
    //             double boxe_projection = dot(axis, boxe[i]);

    //             boxe_min = (boxe_min < boxe_projection) ? boxe_min : boxe_projection;
    //             boxe_max = (boxe_max > boxe_projection) ? boxe_max : boxe_projection;
    //         }

    //         // Theoreme:
    //         // If there is any gap (one disjoint) then there is no collision
    //         if (areDisjoint(boxe_min, boxe_max, sphere_min, sphere_max))
    //         { // We have a gap, there is no collision
    //             return false;
    //         }
    //     }

    //     return true;
    // }

    // bool hasSATCollision(const SphereCollider &sphere, const BoxCollider &boxe)
    // {
    //     return hasSATCollision(boxe, sphere);
    // }
}
