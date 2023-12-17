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
#include "SAT.hpp"
#include "util.hpp"

namespace sne::saintNecPhysics
{
    /**
     * @class SphereCollider
     * @brief SphereCollider physics component
     */
    class SphereCollider : public Collider
    {
    private:
        double _radius;

    public:
        SphereCollider(glm::vec3 center, double radius);
        ~SphereCollider() = default;

        /**
         * @brief Get the Radius object
         *
         * @return const double
         */
        const double getRadius() const;

        bool collide(const Collider *) const override;
        bool collide(const SphereCollider &) const override;
        bool collide(const BoxCollider &) const override;

        bool intersection(const Collider *, const glm::vec3 &axis) const override;
        bool intersection(const SphereCollider &, const glm::vec3 &axis) const override;
        bool intersection(const BoxCollider &, const glm::vec3 &axis) const override;
    };
}