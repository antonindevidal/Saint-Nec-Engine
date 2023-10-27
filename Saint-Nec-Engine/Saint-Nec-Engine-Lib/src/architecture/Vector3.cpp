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


    bool Vector3::operator<(const Vector3 &v) const
    {
        if ((*this) == v)
            return false;

        double hypothenuse1 = sqrt((vect[0] * vect[0] + vect[1] * vect[1])),
               hypothenuse2 = sqrt((v[0] * v[0] + v[1] * v[1])),
               dist_from_origin1 = sqrt(hypothenuse1 * hypothenuse1 + vect[0] * vect[0]),
               dist_from_origin2 = sqrt(hypothenuse2 * hypothenuse2 + v[0] * v[0]);

        // TODO later:
        // Define with our own criteria (x pref, y pref and z pref?)
        return dist_from_origin1 < dist_from_origin2;
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

    // std::ostream& Vector3::operator<<(std::ostream &oss, const Vector3 &v) 
    // {
    //     oss << "(" << vect[0] <<", " << vect[1] << ", " << vect[2] << ")";
    //     return oss;
    // }
}