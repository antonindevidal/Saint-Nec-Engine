#pragma once
#include "architecture/Component.h"
#include "architecture/Vector3.hpp"

namespace saintNecEngine
{

    namespace saintNecPhysics
    {
        class BoxCollider : public saintNecEngine::Component
        {
        private:
            Vector3 _points[8];

        public:
            BoxCollider(Vector3 center, double height, double width, double depth);
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