#pragma once
/**
 * @file GJK.hpp
 * @brief Code implementation of GJK algorithm for collision detection.
 * @author Abdeljalil ZOGHLAMI
 * @date february 6th 2024.
 *
 */


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <architecture/util.hpp>
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"


namespace sne::physics
{

    class GJKIllegalUseException : public std::exception
    {

    public:
        const char *what() const noexcept override
        {
            return "Illegal use of GJK algorithm";
        }
    };

    /**
     * @brief detect collision relating to GJK Theorem algorithm
     * SAT is usefull only for convexe objects
     *
     * Theoreme:
     * If there is any gap (one disjoint) on any axis then there is no collision
     *
     * @return true if collision detected
     * @return false if no collision detected
     */
    template <typename ColliderType1, typename ColliderType2>
    bool hasGJKCollision(const ColliderType1 &, const ColliderType2 &)
    {
        throw GJKIllegalUseException();
    }

    // bool hasSATCollision(const BoxCollider &boxe1, const BoxCollider &boxe2);
    bool hasGJKCollision(const SphereCollider &sphere1, const SphereCollider &sphere2);
    // bool hasSATCollision(const BoxCollider &boxe, const SphereCollider &sphere);
    // bool hasSATCollision(const SphereCollider &sphere, const BoxCollider &boxe);
}
