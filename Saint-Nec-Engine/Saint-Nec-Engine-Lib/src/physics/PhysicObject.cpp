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
        
        void PhysicObject::applyForce(const Forces &)
        {
            
        }

    }
}