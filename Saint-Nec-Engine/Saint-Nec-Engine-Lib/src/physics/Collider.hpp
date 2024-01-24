#pragma once
/**
 * @file Collider.hpp
 * @brief Collider interface.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 23rd 2023.
 *
 */

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <architecture/Component.hpp>

namespace sne::physics
{
    class SphereCollider;
    class BoxCollider;

    class Collider : public Component
    {
    protected:
        glm::vec3 _center;
        Collider(glm::vec3 center) : _center(center) {}

    public:

        /**
         * @brief Destroy the Collider object
         * 
         */
        virtual ~Collider() = default;

        /**
         * @brief Get the Center object
         *
         * @return const vec3&
         */
        const glm::vec3 &getCenter() const
        {
            return _center;
        }

        virtual void setCenter(const glm::vec3 &v)
        {
            _center = v;
        }

        virtual bool collide(const Collider *) const = 0;
        virtual bool collide(const SphereCollider &) const = 0;
        virtual bool collide(const BoxCollider &) const = 0;

        virtual bool intersection(const Collider *, const glm::vec3 &axis) const = 0;
        virtual bool intersection(const SphereCollider &, const glm::vec3 &axis) const = 0;
        virtual bool intersection(const BoxCollider &, const glm::vec3 &axis) const = 0;

        virtual float getMin(const glm::vec3 &axis) const = 0;
    };
}