#pragma once
#include "architecture/Component.hpp"
#include "architecture/Vector3.hpp"
#include <vector>

namespace sne
{

    namespace saintNecPhysics
    {
        class BoxCollider : public sne::Component
        {
        private:
            Vector3 _points[8]; // TO UPDATE
            Vector3 _rotation{0, 0, 0}; // Radian
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
            std::vector<Vector3> getAxis() const;

            static void rotate(Vector3 points[], unsigned int taille, const Vector3 &center, double alpha, double beta, double gamma);
            static void rotate(Vector3 points[], unsigned int taille, const Vector3 &center, const Vector3 &rotation);
        };

        std::ostream &operator<<(std::ostream &oss, const BoxCollider &b);
    }
}