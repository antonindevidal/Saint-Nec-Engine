#pragma once
#include "architecture/Component.hpp"
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
            BoxCollider(const Vector3 center, double width, double depth, double height);
            ~BoxCollider() = default;
            const Vector3& operator[](int) const;
            bool hasPoint(const Vector3 &) const;
        };
    }
}