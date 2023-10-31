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
            Vector3 _rotation{0, 0, 0};
            Vector3 _center;

        public:
            // TO UPDATE
            BoxCollider(const Vector3 center, double width, double depth, double height);
            ~BoxCollider() = default;
            const Vector3 &operator[](int) const;
            bool hasPoint(const Vector3 &) const;
            bool contains(const Vector3 &p, double eps = 1E-3) const;
            int getNbPoints() const;
            void setRotation(const Vector3 v);
            const Vector3 getRotation() const;
        };

        std::ostream &operator<<(std::ostream &oss, const BoxCollider &b);
    }
}