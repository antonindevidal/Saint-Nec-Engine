#include "PhysicObject.hpp"

namespace sne::physics
{
    Time *PhysicObject::time = Time::getInstance();
    PhysicObject::PhysicObject(float mass) : PhysicObject({0, 0, 0}, mass)
    {
    }

    PhysicObject::PhysicObject(const glm::vec3 &position, float mass) : _position(position), _mass(mass)
    {
        if (mass <= 0)
            throw IllegalMassException();
    }

    PhysicObject::~PhysicObject()
    {
        delete _collider;
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

    const Collider *PhysicObject::getCollider() const
    {
        return _collider;
    }

    void PhysicObject::setAcceleration(const glm::vec3 &a)
    {
        if (!isFix)
            _acceleration = a;
    }

    void PhysicObject::setVelocity(const glm::vec3 &v)
    {
        if (!isFix)
            _velocity = v;
    }

    void PhysicObject::setPosition(const glm::vec3 &p)
    {
        _position = p;

        if (_collider)
            _collider->setCenter(_position);
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
        auto tmp = _velocity * dt + ((float)0.5) * _acceleration * dt * dt;
        if (parent)
            parent->translate(tmp);
        _position += tmp;
        _velocity += _acceleration * dt;

        if (_collider)
            _collider->setCenter(_position);
    }

    void PhysicObject::update()
    {
        compute(time->getDeltaTime());
    }

    void PhysicObject::computeCollide(PhysicObject &obj)
    {
        if (!_collider || !obj._collider)
            throw std::exception_ptr();

        try
        {
            if ((isFix && obj.isFix) || !_collider->collide(obj._collider) || (!isFix && hasBeenUpdated) || (!obj.isFix && obj.hasBeenUpdated))
                return;
        }
        catch (const SATIllegalUseException &e)
        {
            if (parent == nullptr)
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
            glm::vec3 axis = _position - obj._position; // To update with impact point
            setVelocity(norm(_velocity) * _amortissement * axis);
        }
        else if (isFix)
        {
            glm::vec3 axis = obj._position - _position; // To update with impact point
            obj.setVelocity(norm(obj._velocity) * obj._amortissement * axis);
        }
        else
        {
            addImpulsion(*this, obj);
        }
        obj.hasBeenUpdated = true;
        hasBeenUpdated = true;
    }

    void addImpulsion(PhysicObject &o1, PhysicObject &o2)
    {
        // Calcul new vitesse
        float v1 = norm(o1.getVelocity()),
              v2 = norm(o2.getVelocity()),
              m1 = o1.getMass(),
              m2 = o2.getMass();

        float newv1 = (m1 - m2) / (m1 + m2) * v1 + 2 * m2 * v2 / (m1 + m2),
              newv2 = 2 * m1 * v1 / (m1 + m2) - (m1 - m2) / (m1 + m2) * v2;

        // Vector orientation
        // Considering line between 2 centers
        // TO UPDATE: considering plan where we touch the other and calcul with normal and angle ?

        glm::vec3 direction = o2.getPosition() - o1.getPosition();
        // std::cout << "ancienne vitesse pour o1" << o1.getVelocity() << "\n";
        // std::cout << "ancienne vitesse pour o2" << o2.getVelocity() << "\n";
        o1.setVelocity(-direction * newv1);
        o2.setVelocity(direction * newv2);
        // std::cout << "nouvelle vitesse pour o1" << o1.getVelocity() << "\n";
        // std::cout << "nouvelle vitesse pour o2" << o2.getVelocity() << "\n";
        // std::cout << "direction: " << direction << "\n";
        // std::cout << "v1: " << v1 << "\n";
        // std::cout << "v2: " << v2 << "\n";
        // std::cout << "v1: " << newv1 << "\n";
        // std::cout << "v2: " << newv2 << "\n";
    }
}