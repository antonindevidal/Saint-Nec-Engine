#include "PhysicObject.hpp"
#include "SAT.hpp"
#include <cmath>
#include "util.hpp"

namespace sne::physics
{
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
        compute(Time::getDeltaTime());
    }

    void PhysicObject::computeCollide(PhysicObject &obj)
    {
        if (!_collider || !obj._collider)
            throw std::exception_ptr();

        try
        {
            if ((isFix && obj.isFix) || !_collider->collide(obj._collider))
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

        _collideCounter++;
        obj._collideCounter++;

        if (obj.isFix)
        {
            glm::vec3 axis = _position - obj._position; // To update with impact point
            setVelocity(norm(_velocity) * _amortissement * axis);

            float min = _collider->getMin(axis),
                  max = _collider->getMax(axis),
                  tmp = obj._collider->getMin(axis);
            float dist = 0;
            if (tmp < min)
            {
                tmp = obj._collider->getMax(axis);
                dist = min - tmp;
            }
            else
            {
                dist = tmp - max;
            }

            _position -= dist * (axis / norm(axis));
        }
        else if (isFix)
        {
            glm::vec3 axis = obj._position - _position; // To update with impact point
            obj.setVelocity(norm(obj._velocity) * obj._amortissement * axis);

            float min = obj._collider->getMin(axis),
                  max = obj._collider->getMax(axis),
                  tmp = _collider->getMin(axis);
            float dist = 0;
            if (tmp < min)
            {
                tmp = _collider->getMax(axis);
                dist = min - tmp;
            }
            else
            {
                dist = tmp - max;
            }

            obj._position -= dist * (axis / norm(axis));
        }
        else
        {
            addImpulsion(*this, obj);
        }

        std::cout << "Collision " << parent->getName() << " - " << obj.parent->getName() << "\n";
        if (parent->getName() == "cube1" || parent->getName() == "cube2")
            std::cout << "Nombre de collision " << parent->getName() << ": " << numberOfCollisions() << "\n";
        if (obj.parent->getName() == "cube1" || obj.parent->getName() == "cube2")
            std::cout << "Nombre de collision " << obj.parent->getName() << ": " << obj.numberOfCollisions() << "\n";
    }

    void addImpulsion(PhysicObject &o1, PhysicObject &o2)
    {
        // Calcul new vitesse
        float v1x = dot(o1.getVelocity(), {1, 0, 0}),
              v1y = dot(o1.getVelocity(), {0, 1, 0}),
              v1z = dot(o1.getVelocity(), {0, 0, 1}),
              v2x = dot(o2.getVelocity(), {1, 0, 0}),
              v2y = dot(o2.getVelocity(), {0, 1, 0}),
              v2z = dot(o2.getVelocity(), {0, 0, 1}),
              m1 = o1.getMass(),
              m2 = o2.getMass();

        float newv1x = (m1 - m2) / (m1 + m2) * v1x + 2 * m2 * v2x / (m1 + m2),
              newv1y = (m1 - m2) / (m1 + m2) * v1y + 2 * m2 * v2y / (m1 + m2),
              newv1z = (m1 - m2) / (m1 + m2) * v1z + 2 * m2 * v2z / (m1 + m2),
              newv2x = 2 * m1 * v1x / (m1 + m2) - (m1 - m2) / (m1 + m2) * v2x,
              newv2y = 2 * m1 * v1y / (m1 + m2) - (m1 - m2) / (m1 + m2) * v2y,
              newv2z = 2 * m1 * v1z / (m1 + m2) - (m1 - m2) / (m1 + m2) * v2z;

        // Vector orientation
        // Considering line between 2 centers
        // TO UPDATE: considering plan where we touch the other and calcul with normal and angle ?

        // Get the normal and old velocity direction
        // glm::vec3 normal = o2.getPosition() - o1.getPosition(),
        //           direction1 = o1.getVelocity() / v1,
        //           direction2 = o2.getVelocity() / v2;
        // normal /= norm(normal);

        // Determine the angle between normal and velocity direction
        // float angle1 = acos(dot(normal, direction1)),
        //       angle2 = acos(dot(normal, direction2));

        // Make rotation considering w
        // glm::vec3 rotationAxis = getNormal(normal, direction1);
        // glm::mat3 R = buildRotationMatrix()
        //     direction1 =

        // std::cout << "ancienne vitesse pour o1" << o1.getVelocity() << o1.parent->getName() << "\n";
        // std::cout << "ancienne vitesse pour o2" << o2.getVelocity() << o2.parent->getName() << "\n";
        o1.setVelocity(glm::vec3{newv1x, newv1y, newv1z});
        o2.setVelocity(glm::vec3{newv2x, newv2y, newv2z});
        // std::cout << "nouvelle vitesse pour o1" << o1.getVelocity() << o1.parent->getName() << "\n";
        // std::cout << "nouvelle vitesse pour o2" << o2.getVelocity() << o2.parent->getName() << "\n";
        // std::cout << "direction: " << direction << "\n";
        // std::cout << "v1: " << v1 << "\n";
        // std::cout << "v2: " << v2 << "\n";
        // std::cout << "v1: " << newv1 << "\n";
        // std::cout << "v2: " << newv2 << "\n";

        glm::vec3 axis = o2.getPosition() - o1.getPosition(); // To update with impact point

        float min = o2.getCollider()->getMin(axis),
              max = o2.getCollider()->getMax(axis),
              tmp = o1.getCollider()->getMin(axis);
        float dist = 0;
        if (tmp < min)
        {
            tmp = o1.getCollider()->getMax(axis);
            dist = min - tmp;
        }
        else
        {
            dist = tmp - max;
        }

        o2.setPosition(o2.getPosition() - dist * (axis / norm(axis)));
    }
}