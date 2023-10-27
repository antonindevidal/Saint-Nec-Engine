#pragma once
#include <cmath>
namespace saintNecEngine
{
	class Vector3
	{
	private:
		double vect[3];

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
	};
}