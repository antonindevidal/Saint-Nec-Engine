#include "Vector3.hpp"

namespace saintNecEngine
{

    Vector3::Vector3() : Vector3(0, 0, 0)
    {
    }

    Vector3::Vector3(const Vector3 &c)
    {
        vect[0] = c[0];
        vect[1] = c[1];
        vect[2] = c[2];
    }

    Vector3::Vector3(double x, double y, double z)
    {
        vect[0] = x;
        vect[1] = y;
        vect[2] = z;
    }

    double &Vector3::operator[](int i)
    {
        return vect[i];
    }

    const double &Vector3::operator[](int i) const
    {
        return vect[i];
    }

    bool Vector3::operator==(const Vector3 &v) const
    {
        return v[0] == vect[0] && v[1] == vect[1] && v[2] == vect[2];
    }

    bool Vector3::operator<(const Vector3 &v) const // TO DISCUSS
    {
        // if ((*this) == v)
        //     return false;

        // double norm1 = norm(*this),
        //        norm2 = norm(v);

        // // TODO later:
        // // Define with our own criteria (x pref, y pref and z pref?)
        // return norm1 < norm2;

        // Critera for delta:
        return vect[0] < v[0] && vect[1] < v[1] && vect[2] < v[2];
    }

    bool Vector3::operator>(const Vector3 &v) const
    {
        return v < (*this);
    }

    bool Vector3::operator>=(const Vector3 &v) const
    {
        return v < (*this) || v == (*this);
    }

    bool Vector3::operator<=(const Vector3 &v) const
    {
        return v > (*this) || v == (*this);
    }

    Vector3 Vector3::operator-(const Vector3 &v) const
    {
        Vector3 res{
            v[0] - vect[0],
            v[1] - vect[1],
            v[2] - vect[2]};

        return res;
    }

    Vector3 Vector3::operator+(const Vector3 &v) const
    {
        Vector3 res{
            v[0] + vect[0],
            v[1] + vect[1],
            v[2] + vect[2]};

        return res;
    }

    // std::ostream& Vector3::operator<<(std::ostream &oss, const Vector3 &v)
    // {
    //     oss << "(" << vect[0] <<", " << vect[1] << ", " << vect[2] << ")";
    //     return oss;
    // }

    double norm(const Vector3 &v)
    {
        return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    Vector3 operator+(const Vector3 &p, double eps)
    {
        return Vector3(p[0] + eps, p[1] + eps, p[2] + eps);
    }

    Vector3 operator-(const Vector3 &p, double eps)
    {
        return Vector3(p[0] - eps, p[1] - eps, p[2] - eps);
    }
}