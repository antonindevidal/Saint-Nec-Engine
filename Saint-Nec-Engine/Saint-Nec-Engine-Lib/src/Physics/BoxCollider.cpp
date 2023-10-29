#include "BoxCollider.hpp"

namespace sne
{

    namespace saintNecPhysics
    {
        BoxCollider::BoxCollider(Vector3 center, double height, double width, double depth)
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

    }
}