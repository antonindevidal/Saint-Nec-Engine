#pragma once
/**
 * @file algorithms.hpp
 * @brief algorithm for collision detection.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 17th 2023.
 *
 */

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <architecture/util.hpp>
#include <algorithm>
#include "util.hpp"
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"
#include <utility>
#include "PhysicObject.hpp"


namespace sne::physics
{
    class SortAxisOnCenter
    {
        const glm::vec3 _axis{1,0,0};
    public:
        bool operator()(const PhysicObject *p1, const PhysicObject *p2) const
        {
            return p1->getCollider()->getMin(_axis) < p2->getCollider()->getMin(_axis);
        }
    };

    /**
     * @brief optimize the number of test for collision detection
     *
     * @return std::vector<std::pair<PhysicObject*, PhysicObject*>>
     */
    template <typename SortFoncteur = SortAxisOnCenter>
    std::vector<std::pair<PhysicObject *, PhysicObject *>> sweepAndPrune(std::vector<PhysicObject *> &);


    template <typename SortFoncteur>
    std::vector<std::pair<PhysicObject *, PhysicObject *>> sweepAndPrune(std::vector<PhysicObject *> &v)
    {
        std::vector<std::pair<PhysicObject *, PhysicObject *>> pairs;

        if (v.size() == 0)
            return pairs;

        std::sort(v.begin(), v.end(), SortFoncteur());

        glm::vec3 axis{1, 0, 0};
        std::vector<PhysicObject *> curr;

        for (unsigned i = 0; i < v.size(); i++)
        {
            v[i]->hasBeenUpdated = false;
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
