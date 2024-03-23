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

namespace sne::physics
{
    const glm::vec3 ORIGIN{0, 0, 0};
    const int GJK_MAX_NUM_ITERATIONS = 100;
    const float EPA_TOLERANCE = 1E-1;
    const int EPA_MAX_NUM_FACES = 6;
    const int EPA_MAX_NUM_LOOSE_EDGES = 32;
    const int EPA_MAX_NUM_ITERATIONS = 64;

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
    bool areDisjoint(float x1_min, float x1_max, float x2_min, float x2_max);

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
     * @brief calculate minkowski difference point from the 2 shape considering 1 direction
     * 
     * @param shape1 
     * @param shape2 
     * @param axis 
     * @return glm::vec3 minkowski point
     */
    glm::vec3 support(const Collider &shape1, const Collider &shape2, const glm::vec3 &axis);
    
    /**
     * @brief tell if there is a collision and, if it is the case, evalute
     * the normal of collision
     * 
     * @param coll1 
     * @param coll2 
     * @param normal normal of collision calculated
     * @return true => collision detected
     * @return false => no collision detected
     */
    bool gjk(const Collider &coll1, const Collider &coll2, glm::vec3 &normal);

    /**
     * @brief tell if there is a collision and, if it is the case, evalute
     * the normal of collision
     * 
     * @param coll1 
     * @param coll2 
     * @param normal normal of collision calculated
     * @return true => collision detected
     * @return false => no collision detected
     */
    bool gjk(const SphereCollider &coll1, const SphereCollider &coll2, glm::vec3 &normal);
    
    /**
     * @brief algorithm used for gjk, triangle construction
     * 
     * @param a 
     * @param b 
     * @param c 
     * @param d 
     * @param simp_dim 
     * @param search_dir 
     */
    void update_simplex3(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, glm::vec3 &d, int &simp_dim, glm::vec3 &search_dir);
    
    /**
     * @brief algorithm used for gjk, tetrahedron construction
     * 
     * @param a 
     * @param b 
     * @param c 
     * @param d 
     * @param simp_dim 
     * @param search_dir 
     * @return true the origine is contained => collision detected
     * @return false 
     */
    bool update_simplex4(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, glm::vec3 &d, int &simp_dim, glm::vec3 &search_dir);
    
    /**
     * @brief algorithm used after gjk to calculate the normal of collision
     * 
     * @param a 
     * @param b 
     * @param c 
     * @param d 
     * @param coll1 
     * @param coll2 
     * @return glm::vec3 
     */
    glm::vec3 EPA(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, const Collider &coll1, const Collider &coll2);
}
