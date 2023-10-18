#include "GameObject.h"

namespace saintNecEngine
{
    GameObject::GameObject(Vector3 &center, Vector3 &rotation)
    {
        _center = center;
        _rotation = rotation;
    }
}