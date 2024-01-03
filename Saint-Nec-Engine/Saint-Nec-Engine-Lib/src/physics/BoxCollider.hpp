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
#include "SAT.hpp"
#include "util.hpp"

namespace sne::saintNecPhysics
{
    /**
     * @class BoxCollider
     * @brief BoxCollider physics component
     */
    class BoxCollider : public Collider
    {
    private:
        glm::vec3 _points[8];         // TO UPDATE
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
        BoxCollider(const glm::vec3 center, double width, double depth, double height);

        /**
         * @brief Destroy the Box Collider object
         *
         */
        ~BoxCollider() = default;

        /**
         * @brief access to point number i
         *
         * @param i
         * @return const glm::vec3&
         */
        const glm::vec3 &operator[](int i) const;

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
         * @brief Set the Rotation object and update points
         *
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

        bool collide(const Collider *) const override;
        bool collide(const SphereCollider &) const override;
        bool collide(const BoxCollider &) const override;

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

        void setCenter(const glm::vec3& v) override
        {
            std::cout << "Mes points: ";
            for(auto elt: _points)
                std:: cout << elt << " ";
            std::cout << "\n";
            _center = v;
        }
    };

    std::ostream &operator<<(std::ostream &oss, const BoxCollider &b);
}
