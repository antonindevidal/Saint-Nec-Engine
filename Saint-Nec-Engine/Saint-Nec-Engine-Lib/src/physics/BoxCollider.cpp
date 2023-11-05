#include "BoxCollider.hpp"
#include <architecture/util.hpp>
#include <iostream>

namespace sne
{

    namespace saintNecPhysics
    {
        BoxCollider::BoxCollider(const glm::vec3 center, double width, double depth, double height)
        {
            double offsetX = width / 2,
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

            _center = center;
        }

        const glm::vec3 &BoxCollider::operator[](int i) const
        {
            return _points[i];
        }

        bool BoxCollider::hasPoint(const glm::vec3 &p) const
        {
            for (glm::vec3 v : _points)
                if (v == p)
                    return true;

            return false;
        }

        int BoxCollider::getNbPoints() const
        {
            return 8;
        }

        bool BoxCollider::contains(const glm::vec3 &p, float eps) const
        {
            for (glm::vec3 v : _points)
            {
                if ((v - eps) <= p && p <= (v + eps))
                    return true;
            }
            return false;
        }

        void BoxCollider::rotate(glm::vec3 points[], unsigned int size, const glm::vec3 &center, double alpha, double beta, double gamma)
        {
            glm::mat3 R = buildRotationMatrix(alpha, beta, gamma);

            for (int index = 0; index < size; index++)
            {
                points[index] -= center;
                points[index] = points[index] * R;
                points[index] += center;
            }
        }

        void BoxCollider::rotate(glm::vec3 points[], unsigned int size, const glm::vec3 &center, const glm::vec3 &rotation)
        {
            rotate(points, size, center, rotation[0], rotation[1], rotation[2]);
        }

        void BoxCollider::setRotation(const glm::vec3 rotation)
        {
            // Evalute the angle of rotation
            glm::vec3 delta_rot = rotation - _rotation;
            double alpha = delta_rot[0],
                   beta = delta_rot[1],
                   gamma = delta_rot[2];

            // Rotate
            rotate(_points, 8, _center, alpha, beta, gamma);
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
                // oss << b[i] << "\n";
                sne::operator<<(oss, b[i]) << "\n";
            }

            return oss;
        }

        // std::vector<glm::vec3> BoxCollider::getAxis() const
        // {
        //     // absolute axis
        //     glm::vec3 axis[] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

        //     // rotate axis considering the state of the Box
        //     rotate(axis, 3, {0, 0, 0}, _rotation);

        //     std::vector<glm::vec3> v{};
        //     v.push_back(axis[0]);
        //     v.push_back(axis[1]);
        //     v.push_back(axis[2]);

        //     return v;
        // }
    }
}