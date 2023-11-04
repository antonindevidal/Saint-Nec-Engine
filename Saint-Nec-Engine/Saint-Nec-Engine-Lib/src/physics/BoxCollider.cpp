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

        // TO UPDATE

        void BoxCollider::rotate(Vector3 points[], unsigned int taille, const Vector3 &center, double alpha, double beta, double gamma)
        {
            // Documentation:
            // https://en.wikipedia.org/wiki/Rotation_matrix#General_3D_rotations

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
            
            // Display Rotation matrix
            // std::cout << "|" << alpha << " " << beta << " " << gamma << "|\n";
            // std::cout << "Rotation matrix:\n";
            // std::cout << "|" << a << " " << b << " " << c << "|\n";
            // std::cout << "|" << d << " " << e << " " << f << "|\n";
            // std::cout << "|" << g << " " << h << " " << i << "|\n";
            
            // Update points
            // Considering p = [x, y, z]^T
            //          | ax + by + cz |
            // R * p =  | dx + ey + fz | = new p
            //          | gx + hy + iz |
            for (int index = 0; index < taille; index++)
            {
                double x = points[index][0] - center[0];
                double y = points[index][1] - center[1];
                double z = points[index][2] - center[2];

                points[index][0] = a * x + b * y + c * z + center[0];
                points[index][1] = d * x + e * y + f * z + center[1];
                points[index][2] = g * x + h * y + i * z + center[2];
            }
        }

        void BoxCollider::rotate(Vector3 points[], unsigned int taille, const Vector3 &center, const Vector3 &rotation)
        {
            rotate(points, taille, center, rotation[0], rotation[1], rotation[2]);
        }

        void BoxCollider::setRotation(const Vector3 rotation)
        {
            Vector3 delta_rot = rotation - _rotation;
            double alpha = delta_rot[0],
                   beta = delta_rot[1],
                   gamma = delta_rot[2];

            rotate(_points, 8, _center, alpha, beta, gamma);
            _rotation = rotation;
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

        std::vector<Vector3> BoxCollider::getAxis() const
        {
            Vector3 axis[] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

            rotate(axis, 3, {0, 0, 0}, _rotation);

            std::vector<Vector3> v{};
            v.push_back(axis[0]);
            v.push_back(axis[1]);
            v.push_back(axis[2]);

            return v;
        }
    }
}