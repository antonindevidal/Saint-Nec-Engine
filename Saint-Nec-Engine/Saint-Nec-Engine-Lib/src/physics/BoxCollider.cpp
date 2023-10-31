#include "BoxCollider.hpp"

namespace saintNecEngine
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

            _center = center;
        }

        const Vector3 &BoxCollider::operator[](int i) const
        {
            return _points[i];
        }

        bool BoxCollider::hasPoint(const Vector3 &p) const
        {
            for (Vector3 v : _points)
                if (v == p)
                    return true;

            return false;
        }

        int BoxCollider::getNbPoints() const
        {
            return 8;
        }

        void BoxCollider::setRotation(const Vector3 rotation)
        {
            // Documentation:
            // https://en.wikipedia.org/wiki/Rotation_matrix#General_3D_rotations

            // Angles calcul
            Vector3 delta_rot = rotation - _rotation;
            double alpha = delta_rot[0],
                   beta = delta_rot[1],
                   gamma = delta_rot[2];

            // Considering the rotation matrix:
            //      |a b c|
            //  R = |d e f|
            //      |g h i|

            double a = cos(alpha) * cos(beta),
                   b = cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma),
                   c = cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma),
                   d = sin(alpha) * cos(beta),
                   e = sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma),
                   f = sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma),
                   g = -sin(beta),
                   h = cos(beta) * sin(gamma),
                   i = cos(beta) * cos(gamma);

            // Update points
            // Considering p = [x, y, z]^T
            //          | ax + by + cz |
            // R * p =  | dx + ey + fz | = new p
            //          | gx + hy + iz |
            for (Vector3 &p : _points)
            {
                double x = p[0] - _center[0],
                       y = p[1] - _center[1],
                       z = p[2] - _center[2];

                p[0] = a * x + b * y + c * z + _center[0];
                p[1] = d * x + e * y + f * z + _center[1];
                p[2] = g * x + h * y + i * z + _center[2];
            }
        }

        const Vector3 BoxCollider::getRotation() const
        {
            return _rotation;
        }

        bool BoxCollider::contains(const Vector3 &p, double eps) const
        {
            // std::cout << "Recherche: " << p << "\n";
            for (Vector3 v : _points)
            {
                // std::cout << "Entre :" << (v-eps) << " et " << (v+eps) << "\n";
                if ((v - eps) <= p && p <= (v + eps))
                    return true;
            }
            return false;
        }

        std::ostream &operator<<(std::ostream &oss, const BoxCollider &b)
        {
            for (int i = 0; i < b.getNbPoints(); i++)
            {
                oss << b[i] << "\n";
            }

            return oss;
        }
    }
}