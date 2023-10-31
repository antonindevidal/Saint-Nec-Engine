#pragma once
#include <cmath>
#include <iostream>

namespace saintNecEngine
{
	class Vector3
	{
	private:
		double vect[3]; // {x, y, z}

	public:
		Vector3();

		Vector3(const Vector3 &c);
		Vector3(double x, double y, double z);
		double &operator[](int i);
		const double &operator[](int i) const;
		bool operator==(const Vector3 &v) const;
		bool operator<(const Vector3 &v) const;
		bool operator>(const Vector3 &v) const;
		bool operator<=(const Vector3 &v) const;
		bool operator>=(const Vector3 &v) const;
		Vector3 operator-(const Vector3 &v) const;
		Vector3 operator+(const Vector3 &v) const;
		friend std::ostream &operator<<(std::ostream &oss, const Vector3 &v)
		{
			oss << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
			return oss;
		}
	};

	template <typename... ARGS>
	double norm(ARGS... xi)
	{
		return sqrt(((xi * xi) + ...));
	}

	double norm(const Vector3 &v);
	Vector3 operator-(const Vector3 &p, double eps);
	Vector3 operator+(const Vector3 &p, double eps);
}