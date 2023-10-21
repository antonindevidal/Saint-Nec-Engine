#pragma once
#include "../../Saint-Nec-Engine-Lib/src/architecture/Component.h"
#include "../../Saint-Nec-Engine-Lib/src/architecture/Vector3.hpp"

namespace Physics
{
    class BoxCollider : public saintNecEngine::Component
    {
        saintNecEngine::Vector3 _points[8];

    public:
        BoxCollider(saintNecEngine::Vector3 center, double height, double width, double deepth);
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