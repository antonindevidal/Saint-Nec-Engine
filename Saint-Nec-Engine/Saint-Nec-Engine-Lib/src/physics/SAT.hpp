#pragma once
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"

namespace saintNecEngine
{

    namespace saintNecPhysics
    {

        bool areDisjoint(double x1_min, double x1_max, double x2_min, double x2_max)
        {
            // Returns true if: [x1_min ; x1_max] ∩ [x2_min; x2_max] = ∅

            return x1_max < x2_min || x2_max < x1_min;
        }

        double dot(const Vector3 v1, const Vector3 v2)
        {
            // If one of the vector norm is 1 then it's a simple projection

            return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
        }

        std::vector<Vector3> operator+(const std::vector<Vector3> v1, const std::vector<Vector3> v2)
        {
            std::vector<Vector3> v = v1;
            for (auto elt : v2)
            {
                v.push_back(elt);
            }

            return v;
        }

        bool hasSATCollision(const BoxCollider &boxe1, const BoxCollider &boxe2)
        {
            // TODO
            // Projection
            // Each BoxCollider has 3 normal axis
            std::vector<Vector3> v1 = boxe1.getAxis();
            std::vector<Vector3> v2 = boxe2.getAxis();
            std::vector<Vector3> v = v1 + v2;

            // SAT
            for (Vector3 axis : v)
            {
                // We check a if a gap exist on each axis
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

                // Theoreme:
                // If there is any gap (one disjoint) then there is no collision
                    
                if (areDisjoint(boxe1_min, boxe1_max, boxe2_min, boxe2_max))
                {    // We have a gap, there is no collision
                    return false;
                }
            }

            // Theoreme:
            // If there is any gap (one disjoint) then there is no collision

            return true;
        }
    }
}