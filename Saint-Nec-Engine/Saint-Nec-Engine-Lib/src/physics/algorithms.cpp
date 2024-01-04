#include "algorithms.hpp"

namespace sne::physics
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

        for (unsigned i = 0; i < v.size(); i++)
        {
            if (curr.size() == 0)
            {
                curr.push_back(v[i]);
            }
            else
            {
                auto it = curr.begin();
                while (it != curr.end() && !(*it)->getCollider()->intersection(v[i]->getCollider(), axis)) it++;
                curr.erase(curr.begin(), it);

                it = curr.begin();
                while(it != curr.end())
                { 
                    pairs.push_back(std::make_pair(v[i], (*it)));
                    ++it;
                }

                curr.push_back(v[i]);
            }
        }

        return pairs;
    }
}
