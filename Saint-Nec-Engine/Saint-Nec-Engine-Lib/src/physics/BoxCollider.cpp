#include "BoxCollider.hpp"

namespace sne
{

    namespace saintNecPhysics
    {
        BoxCollider::BoxCollider(const Vector3 center, double width, double depth, double height)
        {
            double offsetX = width / 2,
                   offsetY = depth / 2,
                   offsetZ = height / 2;

            _points[0] = Vector3(center[0] - offsetX, center[1] - offsetY, center[2] - offsetZ);
            _points[1] = Vector3(center[0] - offsetX, center[1] - offsetY, center[2] + offsetZ);
            _points[2] = Vector3(center[0] - offsetX, center[1] + offsetY, center[2] - offsetZ);
            _points[3] = Vector3(center[0] - offsetX, center[1] + offsetY, center[2] + offsetZ);
            _points[4] = Vector3(center[0] + offsetX, center[1] - offsetY, center[2] - offsetZ);
            _points[5] = Vector3(center[0] + offsetX, center[1] - offsetY, center[2] + offsetZ);
            _points[6] = Vector3(center[0] + offsetX, center[1] + offsetY, center[2] - offsetZ);
            _points[7] = Vector3(center[0] + offsetX, center[1] + offsetY, center[2] + offsetZ);
        }


        const Vector3& BoxCollider::operator[](int i) const
        {
            return _points[i];
        }

        bool BoxCollider::hasPoint(const Vector3 &p) const
        {
            for(Vector3 v: _points)
                if(v == p) return true;

            return false;
        }

        int BoxCollider::getNbPoints() const
        {
            return 8;
        }
    }
}