#pragma once

/**
 * @file util.hpp
 * @brief physics usefull functions
 * @author Abdeljalil ZOGHLAMI
 * @date november 17th 2023.
 */

#include <algorithm>
#include <glm/glm.hpp>
#include <list>
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"
#include "Minkowski.hpp"

namespace sne::physics
{

    const glm::vec3 ORIGIN{0, 0, 0};

    // A renommer => confusion ?
    /**
     * @brief Get the Normal of the 2 axis
     *
     * @return glm::vec3
     */
    glm::vec3 getNormal(const glm::vec3 &, const glm::vec3 &);

    /**
     * @brief tell if: [x1_min ; x1_max] ∩ [x2_min; x2_max] = ∅
     *
     * @param x1_min
     * @param x1_max
     * @param x2_min
     * @param x2_max
     * @return true
     * @return false
     */
    bool areDisjoint(double x1_min, double x1_max, double x2_min, double x2_max);

    /**
     * @brief scalar product v1 . v2
     *
     * @param v1
     * @param v2
     * @return double
     */
    double dot(const glm::vec3 &v1, const glm::vec3 &v2);

    /**
     * @brief check whether or not 2 Colliders intersect on 1 axis
     *
     * @param boxe1
     * @param boxe2
     * @param axis
     * @return true
     * @return false
     */
    bool intersect(const BoxCollider &boxe1, const BoxCollider &boxe2, const glm::vec3 &axis);
    bool intersect(const SphereCollider &sphere1, const SphereCollider &sphere2, const glm::vec3 &axis);
    bool intersect(const SphereCollider &sphere, const BoxCollider &boxe, const glm::vec3 &axis);
    bool intersect(const BoxCollider &boxe, const SphereCollider &sphere, const glm::vec3 &axis);

    /**
     * @brief evalute point obtained with Minkowski difference => C = A - B // { c | c = a-b, a € A et b € B}
     *
     * @param boxe1
     * @param boxe2
     *
     * @return  std::vector<Minkowski>
     */
    std::vector<Minkowski> minkowskiDifference(const BoxCollider &boxe1, const BoxCollider &boxe2);

    /**
     * @brief evaluate the normal of collision reaction
     *
     * @param boxe1
     * @param boxe2
     *
     * @return glm::vec3 representing the axis (normal)
     */
    glm::vec3 collisionNormal(const BoxCollider &boxe1, const BoxCollider &boxe2);
    glm::vec3 collisionNormal(const BoxCollider &boxe, const SphereCollider &sphere);
    glm::vec3 collisionNormal(const SphereCollider &sphere, const BoxCollider &boxe);
    glm::vec3 collisionNormal(const SphereCollider &sphere1, const SphereCollider &sphere2);

    enum MANAGECOLLISION
    {
        NOTHING,
        COLLIDE,
        DONTCOLLIDE,
        OVERLOOP,
        CHECKNEXTPOINT
    };


    class Simplex
    {
        std::array<glm::vec3, 4> points;
        unsigned int n;
        
    public:
        MANAGECOLLISION INFO = MANAGECOLLISION::NOTHING;
        Simplex() : n(0)
        {
            for (int i = 0; i < points.size(); i++)
            {
                points[i] = {0, 0, 0};
            }
        }

        void push_front(glm::vec3 point)
        {
            points = {point, points[0], points[1], points[2]};
            n++;
        }

        glm::vec3 &operator[](unsigned int i)
        {
            return points[i];
        }

        auto size() const
        {
            return n;
        }

        glm::vec3 getClosestPointToOrigin()
        {
            glm::vec3 res = points[0];
            float min = norm(res),
                  curr;

            for (int i = 1; i < points.size(); i++)
            {
                curr = norm(points[i]);
                if (curr < min)
                {
                    min = curr;
                    res = points[i];
                }
            }

            return res;
        }

        void remove(unsigned i)
        {
            for (int j = i - 1; j < 3; j++)
            {
                if (j >= 0)
                    points[j] = points[j + 1];
            }

            n--;
        }
    };

    glm::vec3 support(const Collider &shape1, const Collider &shape2, const glm::vec3 &axis);
    bool gjk(const Collider &A, const Collider &B);
    bool gjk(const SphereCollider &A, const SphereCollider &B);

    using glm::vec3;

    bool sameDirection(const vec3 &v1, const vec3 &v2);
    bool line(Simplex &simplex, vec3 &direction);

    bool triangle(Simplex &simplex, vec3 &direction);

    bool tetrahedron(Simplex &simplex, vec3 &direction);

    bool NextSimplex(Simplex &simplex, glm::vec3 &direction);

}
