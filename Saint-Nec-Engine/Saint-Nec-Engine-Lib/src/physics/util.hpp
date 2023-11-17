#pragma once

/**
 * @file util.hpp
 * @brief physics usefull functions
 * @author Abdeljalil ZOGHLAMI
 * @date november 17th 2023.
 */

#include <glm/glm.hpp>


namespace sne
{

    namespace saintNecPhysics
    {
        glm::vec3 getNormal(const glm::vec3&, const glm::vec3&);
    }   
}