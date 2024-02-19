#pragma once
/**
 * @file BoxCollider.hpp
 * @brief Box to detect collision.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 6rd 2023.
 *
 */

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <architecture/util.hpp>
#include "Collider.hpp"
#include <array>

namespace sne::physics
{
    /**
     * @class BoxCollider
     * @brief BoxCollider physics component
     */
    class BoxCollider : public Collider
    {
    private:
        std::array<glm::vec3, 8> _points;
        glm::vec3 _rotation{0, 0, 0}; // Radian

    public:
        /**
         * @brief Construct a new Box Collider object
         *
         * @param center
         * @param width (X axis)
         * @param depth (Y axis)
         * @param height (Z axis)
         */
        BoxCollider(const glm::vec3 center, float width, float depth, float height);

        /**
         * @brief Destroy the Box Collider object
         *
         */
        ~BoxCollider() override = default;

        /**
         * @brief access to point number i
         *
         * @param i
         * @return const glm::vec3&
         */
        const glm::vec3 &operator[](int i) const;

        /**
         * @brief Set the Center object and update _points
         *
         * @param v
         */
        void setCenter(const glm::vec3 &v) override;

        /**
         * @brief tell if this object contains a point approximatively close to p
         *
         * @param p point to search
         * @param eps approximation, sphere when we can look for this point
         * @return true
         * @return false
         */
        bool hasPoint(const glm::vec3 &p, float eps = 0) const;

        /**
         * @brief Get the Nb Points object
         *
         * @return int
         */
        int getNbPoints() const;

        /**
         * @brief Get Points 
         *
         * @return const std::array<glm::vec3, 8>
         */
        const std::array<glm::vec3, 8> getPoints() const;

        /**
         * @brief Set the Rotation object and update points
         * angles must be passed as Radians
         * @param rotation
         */
        void setRotation(const glm::vec3 rotation);

        /**
         * @brief Get the Rotation object
         *
         * @return const glm::vec3
         */
        const glm::vec3 getRotation() const;

        /**
         * @brief Get the relative Axis of the object
         *
         * @return std::vector<glm::vec3>
         */
        std::vector<glm::vec3> getAxis() const;
        
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

        float getMin(const glm::vec3 &axis) const override;
        float getMax(const glm::vec3 &axis) const override;
        glm::vec3 farthestPoint(const glm::vec3 &axis) const override;
    };

    std::ostream &operator<<(std::ostream &oss, const BoxCollider &b);
}
