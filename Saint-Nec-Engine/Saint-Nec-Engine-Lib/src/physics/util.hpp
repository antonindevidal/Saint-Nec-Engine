#pragma once

/**
 * @file util.hpp
 * @brief physics usefull functions
 * @author Abdeljalil ZOGHLAMI
 * @date november 17th 2023.
 */

#include <glm/glm.hpp>
#include "../architecture/util.hpp"
#include "BoxCollider.hpp"

namespace sne::saintNecPhysics
{
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
    double dot(const glm::vec3 v1, const glm::vec3 v2);

    /**
     * @brief check whether or not 2 box intersect on 1 axis
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
}
