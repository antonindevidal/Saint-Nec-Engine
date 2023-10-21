#pragma once


namespace saintNecEngine
{
    class Vector3
	{ // OpenGL like + permet la fonction d'affichage
		double vect[3];

	public:
		Vector3() : Vector3(0, 0, 0) {} // Pas de 'point par default' ?
        
        Vector3(const Vector3 &c)
        {
            vect[0] = c[0];
            vect[1] = c[1];
            vect[2] = c[2];
        }
		
        Vector3(double x, double y, double z)
		{
			vect[0] = x;
			vect[1] = y;
			vect[2] = z;
		}
		double &operator[](int i)
		{
			return vect[i];
		}

		const double &operator[](int i) const
		{
			return vect[i];
		}
	};
}