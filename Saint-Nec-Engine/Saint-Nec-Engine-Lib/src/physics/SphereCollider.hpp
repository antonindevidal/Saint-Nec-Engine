#pragma once
/**
 * @file SphereCollider.hpp
 * @brief Sphere to detect collision.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 6rd 2023.
 *
 */

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Collider.hpp"

namespace sne::physics
{
    /**
     * @class SphereCollider
     * @brief SphereCollider physics component
     */
    class SphereCollider : public Collider
    {
    private:
        float _radius;

    public:
        SphereCollider(glm::vec3 center, float radius);
        /**
         * @brief Destroy the Sphere Collider object
         * 
         */
        ~SphereCollider() override = default;

        /**
         * @brief Get the Radius object
         *
         * @return const float
         */
        const float getRadius() const;

        bool collide(const Collider *, glm::vec3& normal) const override;
        bool collide(const SphereCollider &, glm::vec3& normal) const override;
        bool collide(const BoxCollider &, glm::vec3& normal) const override;

        /**
         * @brief return true if it has an intersection with other object on axis 
         * 
         * @param axis 
         * @return true 
         * @return false 
         */
        bool intersection(const Collider *, const glm::vec3 &axis) const override;
        bool intersection(const SphereCollider &, const glm::vec3 &axis) const override;
        bool intersection(const BoxCollider &, const glm::vec3 &axis) const override;
        
        /**
         * @brief Get the Min point considering an axis
         * 
         * @param axis 
         * @return float 
         */
        float getMin(const glm::vec3 &axis) const override;

        /**
         * @brief Get the Max point considering an axis
         * 
         * @param axis 
         * @return float 
         */
        float getMax(const glm::vec3 &axis) const override;

        /**
         * @brief Return the farthest point considering a direction
         * 
         * @param axis 
         * @return glm::vec3 
         */
        glm::vec3 farthestPoint(const glm::vec3 &axis) const override;
    };
}