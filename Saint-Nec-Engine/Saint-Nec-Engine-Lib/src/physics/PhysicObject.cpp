#include "PhysicObject.hpp"
#include "../architecture/util.hpp"
#include "SAT.hpp"

namespace sne
{

    namespace saintNecPhysics
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

        void PhysicObject::setCollider(Component *collider)
        {
            _collider = collider;
        }

        void PhysicObject::applyForce(const Force &f)
        {
            _acceleration += f / _mass;
        }

        void PhysicObject::compute(float dt)
        {
            _position += _velocity  * dt + ((float)0.5) * _acceleration  * dt * dt;
            _velocity += _acceleration * dt;
        }

        void PhysicObject::update()
        {
            compute(1 / FPS);
        }

        void PhysicObject::computeCollide(PhysicObject &obj)
        {
            // TODO: later moove this part out of this code to be clean
            if (!_collider || !obj._collider)
                throw std::exception_ptr();
            try
            {
                if (!hasSATCollision(_collider, obj._collider))
                return;
            }
            catch(const SATIllegalUseException &e)
            {
                std::cout << e.what() << '\n';
                std::cerr << e.what() << '\n';
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << '\n';
                std::cerr << e.what() << '\n';
            }
            
            // if(isFixObject)
            // {
            //     // get axis
            //     // _amortissement * V on this axis = NV
            //     // new vitesse = old - NV/_amortissement - NV (cancel + opposite reaction)
                 
            //     // TODO : when not going out -> frottement
            //     // coeff = force opposite / weight
            //     // during position update: counter_acceleration = coeff * weight
            //     // finaly using of cumulativeForces ?
            // }

            addPunctualForce(*this, obj);
        }

        void addPunctualForce(PhysicObject &o1, PhysicObject &o2)
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

            std::cout << "direciton: " << direction << "\n";
            std::cout << "v1 : " << v1 << "\n";
            std::cout << "v2 : " << v2 << "\n";
            o1.setVelocity(-direction * v1);
            o2.setVelocity(direction * v2);
            std::cout << "v1 : " << o1.getVelocity() << "\n";
            std::cout << "v2 : " << o2.getVelocity() << "\n";
        }

    }
}