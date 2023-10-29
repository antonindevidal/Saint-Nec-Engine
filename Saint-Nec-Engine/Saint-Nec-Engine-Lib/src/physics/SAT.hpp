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
            
            return !(x1_min <= x2_min && x2_min <= x1_max || x1_min <= x2_max && x2_max <= x1_max);
        }

        bool hasSATCollision(const BoxCollider &boxe1, const BoxCollider &boxe2)
        {
            // TODO
            // Projection
            // Using rotation

            // SAT

            // X axis
            double x_min_1 = boxe1[0][0],
                   x_max_1 = boxe1[0][0],
                   x_min_2 = boxe2[0][0],
                   x_max_2 = boxe2[0][0];
            // Y axis
            double y_min_1 = boxe1[0][1],
                   y_max_1 = boxe1[0][1],
                   y_min_2 = boxe2[0][1],
                   y_max_2 = boxe2[0][1];
            // Z axis
            double z_min_1 = boxe1[0][2],
                   z_max_1 = boxe1[0][2],
                   z_min_2 = boxe2[0][2],
                   z_max_2 = boxe2[0][2];

            for (int i = 1; i < boxe1.getNbPoints(); i++)
            {
                x_min_1 = (boxe1[i][0] < x_min_1) ? boxe1[i][0] : x_min_1;
                y_min_1 = (boxe1[i][1] < y_min_1) ? boxe1[i][1] : y_min_1;
                y_min_1 = (boxe1[i][2] < z_min_1) ? boxe1[i][2] : z_min_1;

                x_max_1 = (boxe1[i][0] > x_max_1) ? boxe1[i][0] : x_max_1;
                y_max_1 = (boxe1[i][1] > y_max_1) ? boxe1[i][1] : y_max_1;
                z_max_1 = (boxe1[i][2] > z_max_1) ? boxe1[i][2] : z_max_1;

                x_min_2 = (boxe2[i][0] < x_min_2) ? boxe2[i][0] : x_min_2;
                y_min_2 = (boxe2[i][1] < y_min_2) ? boxe2[i][1] : y_min_2;
                z_min_2 = (boxe2[i][2] < z_min_2) ? boxe2[i][2] : z_min_2;

                x_max_2 = (boxe2[i][0] > x_max_2) ? boxe2[i][0] : x_max_2;
                y_max_2 = (boxe2[i][1] > y_max_2) ? boxe2[i][1] : y_max_2;
                z_max_2 = (boxe2[i][2] > z_max_2) ? boxe2[i][2] : z_max_2;
            }

            // Theoreme:
            // If there is any gap (one disjoint) then there is no collision

            return !(areDisjoint(x_min_1, x_max_1, x_min_2, x_max_2) 
                || areDisjoint(y_min_1, y_max_1, y_min_2, y_max_2) 
                || areDisjoint(z_min_1, z_max_1, z_min_2, z_max_2));
        }
    }
}