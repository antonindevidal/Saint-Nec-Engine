#include "BoxCollider.hpp"
#include "SAT.hpp"
#include "util.hpp"

namespace sne::physics
{
    BoxCollider::BoxCollider(const glm::vec3 center, float width, float depth, float height)
        : Collider(center)
    {
        float offsetX = width / 2,
               offsetY = depth / 2,
               offsetZ = height / 2;

        _points[0] = glm::vec3(center[0] - offsetX, center[1] - offsetY, center[2] - offsetZ);
        _points[1] = glm::vec3(center[0] - offsetX, center[1] - offsetY, center[2] + offsetZ);
        _points[2] = glm::vec3(center[0] - offsetX, center[1] + offsetY, center[2] - offsetZ);
        _points[3] = glm::vec3(center[0] - offsetX, center[1] + offsetY, center[2] + offsetZ);
        _points[4] = glm::vec3(center[0] + offsetX, center[1] - offsetY, center[2] - offsetZ);
        _points[5] = glm::vec3(center[0] + offsetX, center[1] - offsetY, center[2] + offsetZ);
        _points[6] = glm::vec3(center[0] + offsetX, center[1] + offsetY, center[2] - offsetZ);
        _points[7] = glm::vec3(center[0] + offsetX, center[1] + offsetY, center[2] + offsetZ);
    }

    const glm::vec3 &BoxCollider::operator[](int i) const
    {
        return _points[i];
    }

    void BoxCollider::setCenter(const glm::vec3 &v)
    {
        glm::vec3 diff = v - _center;
        _center = v;
        for (auto &point : _points)
            point += diff;
    }

    bool BoxCollider::hasPoint(const glm::vec3 &p, float eps) const
    {
        for (const glm::vec3 &v : _points)
            if (areSimilar(v, p, eps))
                return true;

        return false;
    }

    int BoxCollider::getNbPoints() const
    {
        return _points.size();
    }

    const std::array<glm::vec3, 8> BoxCollider::getPoints() const
    {
        return _points;
    }

    void BoxCollider::setRotation(const glm::vec3 rotation)
    {
        // Evalute the angle of rotation
        // rotation is absolute : if rotation == _rotation then angles = 0
        glm::vec3 delta_rot = rotation - _rotation;

        // Rotate
        const glm::mat3 R = buildRotationMatrix(delta_rot[0], delta_rot[1], delta_rot[2]);
        for (int i = 0; i < _points.size(); i++)
            rotate(R, _points[i], _center);

        // Update new rotation
        _rotation = rotation;
    }

    const glm::vec3 BoxCollider::getRotation() const
    {
        return _rotation;
    }

    std::ostream &operator<<(std::ostream &oss, const BoxCollider &b)
    {
        for (int i = 0; i < b.getNbPoints(); i++)
        {
            oss << b[i] << "\n";
        }

        return oss;
    }

    std::vector<glm::vec3> BoxCollider::getAxis() const
    {
        // absolute axis
        std::vector<glm::vec3> v{}, v2{};
        v.push_back({1, 0, 0});
        v.push_back({0, 1, 0});
        v.push_back({0, 0, 1});

        // rotate axis considering the state of the Box
        const glm::mat3 R = buildRotationMatrix(_rotation);
        glm::vec3 center{0, 0, 0};
        for (int i = 0; i < v.size(); i++)
            rotate(R, v[i], center);

        return v;
    }

    bool BoxCollider::collide(const Collider *c, glm::vec3& normal) const
    {
        return c->collide(*this, normal);
    }

    bool BoxCollider::collide(const SphereCollider &s, glm::vec3& normal) const
    {
        return gjk(*this, s, normal);
    }
    bool BoxCollider::collide(const BoxCollider &b, glm::vec3& normal) const
    {
        return gjk(*this, b, normal);
    }

    bool BoxCollider::intersection(const Collider *c, const glm::vec3 &axis) const
    {
        return c->intersection(*this, axis);
    }

    bool BoxCollider::intersection(const SphereCollider &s, const glm::vec3 &axis) const
    {
        return intersect(*this, s, axis);
    }

    bool BoxCollider::intersection(const BoxCollider &b, const glm::vec3 &axis) const
    {
        return intersect(*this, b, axis);
    }

    float BoxCollider::getMin(const glm::vec3 &axis) const
    {
        float min = dot(axis, _points[0]);
        for (unsigned i = 1; i < _points.size(); i++)
        {
            float v = dot(axis, _points[i]);
            min = (v < min) ? v : min;
        }

        return min;
    }

    float BoxCollider::getMax(const glm::vec3 &axis) const
    {
        float max = dot(axis, _points[0]);
        for (unsigned i = 1; i < _points.size(); i++)
        {
            float v = dot(axis, _points[i]);
            max = (v > max) ? v : max;
        }

        return max;
    }

    glm::vec3 BoxCollider::farthestPoint(const glm::vec3 &axis) const
    {
        float max = dot(axis, _points[0]);
        glm::vec3 res = _points[0];
        for (unsigned i = 1; i < _points.size(); i++)
        {
            float projection = dot(_points[i], axis);
            if(projection > max)
            {
                max = projection;
                res = _points[i];
            }
            
        }

        return res;
    }

}
