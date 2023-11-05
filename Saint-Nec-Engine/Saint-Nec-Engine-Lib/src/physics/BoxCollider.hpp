#pragma once
#include "architecture/Component.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace sne
{

    namespace saintNecPhysics
    {
        /**
         * @class BoxCollider
         * @brief BoxCollider physics component
         */
        class BoxCollider : public sne::Component
        {
        private:
            glm::vec3 _points[8];         // TO UPDATE
            glm::vec3 _rotation{0, 0, 0}; // Radian
            glm::vec3 _center;

        public:
            /**
             * @brief Construct a new Box Collider object
             * 
             * @param center 
             * @param width 
             * @param depth 
             * @param height 
             */
            BoxCollider(const glm::vec3 center, double width, double depth, double height);

            /**
             * @brief Destroy the Box Collider object
             * 
             */
            ~BoxCollider() = default;

            /**
            * 
            * Create multicolor cube of size 1*1*1.
            * 
            * @param i index of the point we aer looking for.
            */
            const glm::vec3 &operator[](int i) const;

            /**
             * @brief Tell if the point is present
             * 
             * @return true 
             * @return false 
             */
            bool hasPoint(const glm::vec3 &) const;

            /**
             * @brief tell if this object contains a point approximatively close to p
             * 
             * @param p point to search
             * @param eps approximation, sphere when we can look for this point
             * @return true 
             * @return false 
             */
            bool contains(const glm::vec3 &p, float eps = 1E-3) const;

            /**
             * @brief Get the Nb Points object
             * 
             * @return int 
             */
            int getNbPoints() const;

            /**
             * @brief Set the Rotation object and update points
             * 
             * @param rotation
             */
            void setRotation(const glm::vec3 rotation);

            /**
             * @brief Get the Rotation object
             * 
             * @return const glm::vec3 
             */
            const glm::vec3 getRotation() const;

            /**
             * @brief Get the relative Axis of the object
             * 
             * @return std::vector<glm::vec3> 
             */
            // std::vector<glm::vec3> getAxis() const;

            /**
             * @brief 
             * 
             * @param points array of the point to rotate
             * @param size number of points
             * @param center rotation center
             * @param alpha rotation angle for 1st axis
             * @param beta rotation angle for 2nd axis
             * @param gamma rotation angle for 3rd axis
             */
            static void rotate(glm::vec3 points[], unsigned int size, const glm::vec3 &center, double alpha, double beta, double gamma);
            static void rotate(glm::vec3 points[], unsigned int size, const glm::vec3 &center, const glm::vec3 &rotation);
        };

        std::ostream &operator<<(std::ostream &oss, const BoxCollider &b);
    }
}