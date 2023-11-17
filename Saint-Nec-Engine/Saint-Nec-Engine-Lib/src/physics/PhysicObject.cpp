#include "PhysicObject.hpp"

namespace sne
{

    namespace saintNecPhysics
    {
        PhysicObject::PhysicObject()
        {
        }

        PhysicObject::PhysicObject(const glm::vec3 &position)
        {
            _position = position;
        }

        const glm::vec3 &PhysicObject::getAcceleration() const
        {
            return _acceleration;
        }

        const glm::vec3 &PhysicObject::getVelocity() const
        {
            return _velocity;
        }

        const glm::vec3 &PhysicObject::getPosition() const
        {
            return _position;
        }

        const glm::vec3 &PhysicObject::getRotation() const
        {
            return _rotation;
        }

        float PhysicObject::getAmortissement() const
        {
            return _amortissement;
        }

        float PhysicObject::getMass() const
        {
            return _mass;
        }

        void PhysicObject::setAcceleration(const glm::vec3 &a)
        {
            _acceleration = a;
        }

        void PhysicObject::setVelocity(const glm::vec3 &v)
        {
            _velocity = v;
        }

        void PhysicObject::setPosition(const glm::vec3 &p)
        {
            _position = p;
        }

        void PhysicObject::setRotation(const glm::vec3 &r)
        {
            _rotation = r;
        }

        void PhysicObject::setMass(float m)
        {
            _mass = m;
        }

        void PhysicObject::applyForce(const Force &)
        {
        }

    }
}