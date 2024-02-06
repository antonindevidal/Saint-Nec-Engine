#include "GJK.hpp"
#include <algorithm>
#include "util.hpp"
#include "Minkowski.hpp"

namespace sne::physics
{
    bool hasGJKCollision(const BoxCollider &boxe1, const BoxCollider &boxe2)
    {
        std::vector<Minkowski> minkowskiSum;

        for(auto &point: boxe1.getPoints())
            for(auto &point2: boxe2.getPoints())
                minkowskiSum.push_back(Minkowski{point, point2, false});
        
        

        return true;
    }

    bool hasGJKCollision(const SphereCollider &sphere1, const SphereCollider &sphere2)
    {
        // Evaluate the distance between the 2 centers
        double distance = norm(sphere1.getCenter() - sphere2.getCenter());
        return distance <= (sphere1.getRadius() + sphere2.getRadius());
    }
}
