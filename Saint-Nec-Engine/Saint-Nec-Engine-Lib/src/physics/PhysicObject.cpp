#include "PhysicObject.hpp"
#include "../architecture/util.hpp"

namespace sne
{

    namespace saintNecPhysics
    {
        PhysicObject::PhysicObject(float mass) : PhysicObject({0, 0, 0}, mass)
        {
        }

        PhysicObject::PhysicObject(const glm::vec3 &position, float mass) : _position(position), _mass(mass)
        {
            if(mass<=0)
                throw IllegalMassException();
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

        void PhysicObject::applyForce(const Force &f)
        {
        }

        void PhysicObject::compute(float dt)
        {
            _position += _velocity * dt + ((float)0.5) * _acceleration * dt * dt;
            _velocity += _acceleration * dt;
        }

        void PhysicObject::update()
        {
            compute(1 / FPS);
        }

        void PhysicObject::computeCollide(PhysicObject &obj)
        {
            // Calcul new vitesse
            float v1 = norm(_velocity),
                  v2 = norm(obj._velocity),
                  m1 = _mass,
                  m2 = obj._mass;

            v1 = (m1 - m2) / (m1 + m2) * v1 + 2 * m2 * v2 / (m1 + m2);
            v2 = 2 * m1 * v1 / (m1 + m2) - (m1 - m2) / (m1 + m2) * v2;

            // Vector orientation
            // Considering line between 2 centers
            // TO UPDATE: considering plan where we touch the other and calcul with normal and angle ?
            glm::vec3 direction = _position - obj._position;

            std::cout << "direciton: " << direction << "\n";
            std::cout << "v1 : " << v1 << "\n";
            std::cout << "v2 : " << v2 << "\n";
            _velocity = -direction * v1;
            obj._velocity = direction * v2;
            std::cout << "v1 : " << _velocity << "\n";
            std::cout << "v2 : " << obj._velocity << "\n";
        }

    }
}