#include "util.hpp"


glm::vec3 getNormal(const glm::vec3& v1, const glm::vec3& v2)
{
    return glm::cross(v1, v2);
}