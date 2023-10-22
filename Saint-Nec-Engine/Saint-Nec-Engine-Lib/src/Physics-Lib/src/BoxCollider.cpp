#include "BoxCollider.hpp"

namespace Physics
{
    BoxCollider::BoxCollider(saintNecEngine::Vector3 center, double height, double width, double deepth)
    {
        double  offsetX = width/2,
                offsetY = deepth/2,
                offsetZ = height/2;

        _points[0] = saintNecEngine::Vector3(center[0] - offsetX, center[1] - offsetY, center[2] - offsetZ);
        _points[1] = saintNecEngine::Vector3(center[0] - offsetX, center[1] - offsetY, center[2] + offsetZ);
        _points[2] = saintNecEngine::Vector3(center[0] - offsetX, center[1] + offsetY, center[2] - offsetZ);
        _points[3] = saintNecEngine::Vector3(center[0] - offsetX, center[1] + offsetY, center[2] + offsetZ);
        _points[4] = saintNecEngine::Vector3(center[0] + offsetX, center[1] - offsetY, center[2] - offsetZ);
        _points[5] = saintNecEngine::Vector3(center[0] + offsetX, center[1] - offsetY, center[2] + offsetZ);
        _points[6] = saintNecEngine::Vector3(center[0] + offsetX, center[1] + offsetY, center[2] - offsetZ);
        _points[7] = saintNecEngine::Vector3(center[0] + offsetX, center[1] + offsetY, center[2] + offsetZ);
    }

}
