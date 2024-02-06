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

    double dot(const glm::vec3 &v1, const glm::vec3 &v2)
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

    std::vector<Minkowski> minkowskiDifference(const BoxCollider &boxe1, const BoxCollider &boxe2)
    {
        std::vector<Minkowski> v;

        for (int i = 0; i < boxe1.getNbPoints(); i++)
        {
            for (int j = 0; j < boxe2.getNbPoints(); j++)
            {
                v.push_back(Minkowski{boxe1[i], boxe2[j]});
            }
        }

        std::sort(v.begin(), v.end(), [](const Minkowski &p1, const Minkowski &p2)
                  { return p1.getDistance() < p2.getDistance(); });

        return v;
    }

    std::vector<Minkowski> minkowskiDifference(const BoxCollider &boxe, const SphereCollider &sphere)
    {
        std::vector<Minkowski> v;

        for (int i = 0; i < boxe.getNbPoints(); i++)
        {
            v.push_back(Minkowski{boxe[i], sphere.getCenter()});
        }

        std::sort(v.begin(), v.end(), [](const Minkowski &p1, const Minkowski &p2)
                  { return p1.getDistance() < p2.getDistance(); });

        return v;
    }

    glm::vec3 collisionNormal(const BoxCollider &boxeA, const BoxCollider &boxeB)
    {
        std::vector<Minkowski> v = minkowskiDifference(boxeA, boxeB);
        glm::vec3 pointA1 = v[0].getPointA(),
                  pointA2 = v[1].getPointA(),
                  pointA3 = v[2].getPointA(),
                  pointA4 = v[3].getPointA();

        // Get directions
        glm::vec3 axis1 = pointA2 - pointA1,
                  axis2 = pointA3 - pointA1,
                  axis3 = pointA4 - pointA1;

        // Normalize
        axis1 = (norm(axis1) == 0) ? axis1 : axis1/norm(axis1);
        axis2 = (norm(axis2) == 0) ? axis2 : axis2/norm(axis2);
        axis3 = (norm(axis3) == 0) ? axis3 : axis3/norm(axis3);

        std::cout<< "LAaaaaaaaaaaa\n";
        std::cout << " axis 1:" << axis1 << "\n";
        std::cout << " axis 1:" << axis2 << "\n";
        std::cout << " axis 1:" << axis3 << "\n";
        std::cout << " point3 1:" << pointA1 << "\n";
        std::cout << " point3 1:" << pointA2 << "\n";
        std::cout << " point3 1:" << pointA3 << "\n";
        std::cout << " point3 1:" << pointA4 << "\n";
        // Get opposite direction
        return axis1 + axis2 + axis3;

        // TO UPDATE, 2 axis for each ?
        /*glm::vec3 pointB1 = v[0].getPointB(),
            pointB2 = v[1].getPointB(),
            pointB3 = v[2].getPointB(),
            pointB4 = v[3].getPointB();*/
    }

    glm::vec3 collisionNormal(const BoxCollider &boxe, const SphereCollider &sphere)
    {
        std::vector<Minkowski> v = minkowskiDifference(boxe, sphere);
        glm::vec3 pointA1 = v[0].getPointA(),
                  pointA2 = v[1].getPointA(),
                  pointA3 = v[2].getPointA(),
                  pointA4 = v[3].getPointA();
        
        // Get directions
        glm::vec3 axis1 = pointA2 - pointA1,
                  axis2 = pointA3 - pointA1,
                  axis3 = pointA4 - pointA1;
                  
        // Normalize
        axis1 /= norm(axis1);
        axis2 /= norm(axis2);
        axis3 /= norm(axis3);

        // Get opposite direction
        return axis1 + axis2 + axis3;
    }

    glm::vec3 collisionNormal(const SphereCollider &sphere, const BoxCollider &boxe)
    {
        return collisionNormal(boxe, sphere);
    }

    glm::vec3 collisionNormal(const SphereCollider &sphere1, const SphereCollider &sphere2)
    {
        return sphere2.getCenter() - sphere1.getCenter();
    }
}