#pragma once

/**
 * @file BoxCollider.hpp
 * @brief Box to detect collision.
 * @author Abdeljalil ZOGHLAMI
 * @date november 17th 2023.
 */

#include "architecture/GameObject.hpp"
#include <glm/glm.hpp>

namespace sne
{

    namespace saintNecPhysics
    {
        class Interaction : public GameObject
        {
            glm::vec3 acceleration{0, 0, -9.81};
            glm::vec3 velocity{0, 0, 0};

        public:
            Interaction();
            ~Interaction() = default;
        };
    }
}