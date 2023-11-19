#include "BoxCollider.hpp"
#include "SphereCollider.hpp"
#include "SAT.hpp"
#include <architecture/util.hpp>

namespace sne
{

    namespace saintNecPhysics
    {

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

        std::vector<glm::vec3> operator+(const std::vector<glm::vec3> v1, const std::vector<glm::vec3> v2)
        {
            std::vector<glm::vec3> v = v1;
            for (auto elt : v2)
            {
                v.push_back(elt);
            }

            return v;
        }

        bool hasSATCollision(const BoxCollider &boxe1, const BoxCollider &boxe2)
        {
            // Each BoxCollider has 3 normal axis
            std::vector<glm::vec3> v1 = boxe1.getAxis();
            std::vector<glm::vec3> v2 = boxe2.getAxis();
            std::vector<glm::vec3> v = v1 + v2;

            // SAT
            for (glm::vec3 axis : v)
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
                { // We have a gap, there is no collision
                    return false;
                }
            }

            // We didn't find any gap
            return true;
        }

        bool hasSATCollision(const SphereCollider &sphere1, const SphereCollider &sphere2)
        {
            // Evaluate the distance between the 2 centers
            double distance = norm(sphere1.getCenter() - sphere2.getCenter());
            return distance <= (sphere1.getRadius() + sphere2.getRadius());
        }

        bool hasSATCollision(const BoxCollider &boxe, const SphereCollider &sphere)
        {
            // Evaluate the distance between the 2 centers
            std::vector<glm::vec3> v = boxe.getAxis();

            // SAT
            for (glm::vec3 axis : v)
            {
                // We check a if a gap exist on each axis
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

        bool hasSATCollision(Component *elt1, Component *elt2)
        {
            BoxCollider *box1 = dynamic_cast<BoxCollider *>(elt1);
            BoxCollider *box2 = dynamic_cast<BoxCollider *>(elt2);
            SphereCollider *sphere1 = dynamic_cast<SphereCollider *>(elt1);
            SphereCollider *sphere2 = dynamic_cast<SphereCollider *>(elt2);

            if (box1 && box2)
            {
                return hasSATCollision(*box1, *box2);
            }
            else if (sphere1 && sphere2)
            {
                return hasSATCollision(*sphere1, *sphere2); 
            }
            else if ((box1 && sphere2) || (sphere1 && box2))
            {
                if(!box1)
                    box1 = box2;
                if(!sphere1)
                    sphere1 = sphere2;
                return hasSATCollision(*box1, *sphere1);
            }
            
            throw new SATIllegalUseException();
        }
    }
}