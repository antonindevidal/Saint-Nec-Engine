#ifndef FORME_HPP_2023
#define FORME_HPP_2023
#include "GameObject.h"

namespace saintNecEngine
{

    class Forme : public GameObject
    {
        // using Point = Vector3; Si tu préfères un alias pour cette partie
    protected:
    public:
        std::vector<Vector3> Points; // Je la repasserai en protected
        Forme() = default;           // Idem
        Forme(Vector3 &center, Vector3 &rotation);
        virtual ~Forme() = default;
        void addPoint(Vector3 &); // Ne me plait pas pour l'héritage, à voir
        void addPoint(double, double, double);
    };

    // En général je garde celle là dans le hpp, dis moi si tu n'aimes pas
    std::ostream &operator<<(std::ostream &oss, const Forme &f)
    {
        for (Vector3 v : f.Points)
            oss << v << "\n";
        return oss;
    }

    class Square : public Forme
    {

    public:
        Square(Vector3 &center, Vector3 &rotation, double);
        virtual ~Square() = default;
    };

    
}

#endif