#include "algorithms.hpp"

namespace sne::saintNecPhysics
{
    std::vector<std::pair<PhysicObject *, PhysicObject *>> sweepAndPrune(std::vector<PhysicObject *> &v)
    {
        std::vector<std::pair<PhysicObject *, PhysicObject *>> pairs;

        if (v.size() == 0)
            return pairs;

        // Sort object
        std::sort(v.begin(), v.end(),
                  [](PhysicObject *p1, PhysicObject *p2)
                  {
                      return p1->getPosition()[0] < p2->getPosition()[0]; // to update for min point axis
                  });

        glm::vec3 axis{1, 0, 0};
        std::vector<PhysicObject *> curr;

        for (int i = 0; i < v.size(); i++)
        {
            // For each object
            for (std::vector<PhysicObject *>::iterator elt = curr.begin(); elt != curr.end(); elt++)
            {

                // We compare with previous object with wich one it's possible to collide
                if ((*elt)->getCollider()->intersection(v[i]->getCollider(), axis))
                {
                    // Collision possible so we add this pair
                    curr.push_back(v[i]);
                    pairs.push_back(std::make_pair(v[i], *elt));
                }
                else
                {
                    // Impossible collision, so we remove this object that can not collide with the others because it's sorted
                    curr.erase(elt);
                }
            }
        }

        return pairs;
    }
}
