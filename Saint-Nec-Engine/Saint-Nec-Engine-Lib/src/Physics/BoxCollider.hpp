#pragma once
#include "src/architecture/Component.h"
#include "src/architecture/Vector3.hpp"

namespace saintNecEngine
{

    namespace saintNecPhysics
    {
        class BoxCollider : public saintNecEngine::Component
        {
            Vector3 _points[8];

        public:
            BoxCollider(Vector3 center, double height, double width, double deepth);
            void update() override
            {
                // Je suis une fraude
            }

            void draw() const override
            {
                // Je suis une fraude
            }
        };
    }
}