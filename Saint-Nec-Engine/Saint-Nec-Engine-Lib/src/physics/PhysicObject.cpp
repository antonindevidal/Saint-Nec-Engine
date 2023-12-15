#include "PhysicObject.hpp"

namespace sne::saintNecPhysics
{
    PhysicObject::PhysicObject(float mass) : PhysicObject({0, 0, 0}, mass)
    {
    }

    PhysicObject::PhysicObject(const glm::vec3 &position, float mass) : _position(position), _mass(mass)
    {
        if (mass <= 0)
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

    void PhysicObject::setCollider(Collider *collider)
    {
        _collider = collider;
    }

    void PhysicObject::applyForce(const Force &f)
    {
        _acceleration += f / _mass;
    }

    void PhysicObject::compute(float dt)
    {
        _position += _velocity * dt + ((float)0.5) * _acceleration * dt * dt;
        _velocity += _acceleration * dt;

        if (_collider)
            _collider->setCenter(_position);
    }

    void PhysicObject::update() // to remove it would be bad use of getdelta?
    {
        compute(1 / FPS);
    }

    void PhysicObject::computeCollide(PhysicObject &obj)
    {
        if (!_collider || !obj._collider)
            throw std::exception_ptr();

        try
        {
            if (!_collider->collide(obj._collider))
                return;
        }
        catch (const SATIllegalUseException &e)
        {
            if(parent == nullptr)
                std::cout << " ";
            else
                std::cout << e.what() << " " << parent->getName() << "\n";
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << " " << parent->getName() << "\n";
            throw std::exception();
        }

        if (obj.isFix)
        {
            // We don't need to test this.isFix bc we won't use it
            glm::vec3 axis = obj._position - _position; // To update with impact point
            _velocity = norm(_velocity) * _amortissement * axis;
        }
        else
        {
            addImpulsion(*this, obj);
        }
    }

    void addImpulsion(PhysicObject &o1, PhysicObject &o2)
    {
        // Calcul new vitesse
        float v1 = norm(o1.getVelocity()),
              v2 = norm(o2.getVelocity()),
              m1 = o1.getMass(),
              m2 = o2.getMass();

        v1 = (m1 - m2) / (m1 + m2) * v1 + 2 * m2 * v2 / (m1 + m2);
        v2 = 2 * m1 * v1 / (m1 + m2) - (m1 - m2) / (m1 + m2) * v2;

        // Vector orientation
        // Considering line between 2 centers
        // TO UPDATE: considering plan where we touch the other and calcul with normal and angle ?
        glm::vec3 direction = o1.getPosition() - o2.getPosition();
        o1.setVelocity(-direction * v1);
        o2.setVelocity(direction * v2);
    }
}