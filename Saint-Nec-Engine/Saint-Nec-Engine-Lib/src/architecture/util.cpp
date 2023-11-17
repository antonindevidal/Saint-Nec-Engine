#include "util.hpp"

namespace glm
{

    bool operator==(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2];
    }

    bool operator<(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return v1[0] < v2[0] && v1[1] < v2[1] && v1[2] < v2[2];
    }

    bool operator>(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return v2 < v1;
    }

    bool operator>=(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return v2 < v1 || v1 == v2;
    }

    bool operator<=(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return v2 > v1 || v2 == v1;
    }

    glm::vec3 operator-(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        glm::vec3 res{
            v1[0] - v2[0],
            v1[1] - v2[1],
            v1[2] - v2[2]};

        return res;
    }

    glm::vec3 operator+(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        glm::vec3 res{
            v1[0] + v2[0],
            v1[1] + v2[1],
            v1[2] + v2[2]};

        return res;
    }

    glm::vec3 operator+(const glm::vec3 &p, float &eps)
    {
        return glm::vec3{p[0] + eps, p[1] + eps, p[2] + eps};
    }

    glm::vec3 operator-(const glm::vec3 &p, float &eps)
    {
        return glm::vec3{p[0] - eps, p[1] - eps, p[2] - eps};
    }

    std::ostream &operator<<(std::ostream &oss, const glm::vec3 &v)
    {
        oss << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
        return oss;
    }
}

namespace sne
{
    bool areSimilar(const glm::vec3 &v1, const glm::vec3 &v2, float eps)
    {
        if ((v1 - eps) <= v2 && v2 <= (v1 + eps))
            return true;
            
        return false;
    }
    
    double norm(const glm::vec3 &v)
    {
        return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    glm::mat3 buildRotationMatrix(float alpha, float beta, float gamma)
    {
        // Documentation:
        // https://en.wikipedia.org/wiki/Rotation_matrix#General_3D_rotations

        // Considering the rotation matrix:
        //      |a b c|
        //  R = |d e f|
        //      |g h i|

        // double a = cos(alpha) * cos(beta),
        //        b = cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma),
        //        c = cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma),
        //        d = sin(alpha) * cos(beta),
        //        e = sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma),
        //        f = sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma),
        //        g = -sin(beta),
        //        h = cos(beta) * sin(gamma),
        //        i = cos(beta) * cos(gamma);

        return glm::mat3{
            cos(alpha) * cos(beta), cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma), cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma),
            sin(alpha) * cos(beta), sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma), sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma),
            -sin(beta), cos(beta) * sin(gamma), cos(beta) * cos(gamma)};
    }

    glm::mat3 buildRotationMatrix(const glm::vec3 &rotation)
    {
        return buildRotationMatrix(rotation[0], rotation[1], rotation[2]);
    }

    void displayRotationMatrix(glm::mat3 &R, float alpha, float beta, float gamma)
    {

        std::cout << "|" << alpha << " " << beta << " " << gamma << "|\n";
        std::cout << "Rotation matrix:\n";
        for (int i = 0; i < 3; ++i)
        {
            std::cout << "|";
            for (int j = 0; j < 3; ++j)
            {
                std::cout << R[i][j] << " ";
            }
            std::cout << "|\n";
        }
    }

    void rotate(const glm::mat3 &R, glm::vec3 &point, const glm::vec3 &center)
    {
        point -= center;
        point = point * R;
        point += center;
    }
}