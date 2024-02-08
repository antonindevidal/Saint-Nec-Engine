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

    

    template <int N= 4>
    struct Simplex
    {
        std::list<glm::vec3> points;
        int n = 0;

        void addPoint(const glm::vec3 &point)
        {
            points.push_front(point);
            n++;

            if(n == N)
                removePoint();
        }

        void removePoint()
        {
            n--;
            points.pop_back();
        }

        glm::vec3 getClosestPointToOrigin()
        {
            auto v = points.begin();
            float min = norm(*v),
                curr;

            for (auto it=++points.begin(); it!=points.end(); ++it)
            {
                curr = norm(*it);
                if(curr < min)
                {
                    min = curr;
                    v = it;
                }
            }

            return *v;
        }
    };
    
    glm::vec3 support(const Collider &shape1, const Collider &shape2, const glm::vec3 &axis);
    bool gjk(const Collider &A, const Collider &B, const glm::vec3 &initialDirection={1, 0, 0});
    bool gjk(const SphereCollider &A, const SphereCollider &B);

}
