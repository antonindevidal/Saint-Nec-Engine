#pragma once
/**
 * @file SAT.hpp
 * @brief Code implementation of SAT algorithm for collision detection.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 6rd 2023.
 *
 */


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <architecture/util.hpp>
#include "util.hpp"
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"


namespace sne::physics
{

    class SATIllegalUseException : public std::exception
    {

    public:
        const char *what() const noexcept override
        {
            return "Illegal use of SAT algorithm";
        }
    };

    /**
     * @brief concatenation of v1 and v2 into an other vector
     *
     * @param v1
     * @param v2
     * @return std::vector<glm::vec3>
     */
    std::vector<glm::vec3> operator+(const std::vector<glm::vec3> v1, const std::vector<glm::vec3> v2);

    /**
     * @brief detect collision relating to Separate Axis Theorem algorithm
     * SAT is usefull only for convexe objects
     *
     * Theoreme:
     * If there is any gap (one disjoint) on any axis then there is no collision
     *
     * @return true if collision detected
     * @return false if no collision detected
     */
    template <typename ColliderType1, typename ColliderType2>
    bool hasSATCollision(const ColliderType1 &, const ColliderType2 &)
    {
        throw new SATIllegalUseException();
    }

    bool hasSATCollision(const BoxCollider &boxe1, const BoxCollider &boxe2);
    bool hasSATCollision(const SphereCollider &sphere1, const SphereCollider &sphere2);
    bool hasSATCollision(const BoxCollider &boxe, const SphereCollider &sphere);
    bool hasSATCollision(const SphereCollider &sphere, const BoxCollider &boxe);
}
