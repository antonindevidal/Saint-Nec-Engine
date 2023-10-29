#pragma once
#include "architecture/Component.h"
#include "architecture/Vector3.hpp"

namespace sne
{

    namespace saintNecPhysics
    {
        class BoxCollider : public sne::Component
        {
        private:
            Vector3 _points[8];

        public:
            BoxCollider(Vector3 center, double height, double width, double depth);
            ~BoxCollider() = default;
        };
    }
}