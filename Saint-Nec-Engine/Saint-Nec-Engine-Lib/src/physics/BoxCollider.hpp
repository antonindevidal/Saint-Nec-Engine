#pragma once
/**
 * @file BoxCollider.hpp
 * @brief Box to detect collision.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 6rd 2023.
 *
 */

#include "architecture/Component.hpp"
#include "architecture/Vector3.hpp"
#include <vector>

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
            Vector3 _points[8];         // TO UPDATE
            Vector3 _rotation{0, 0, 0}; // Radian
            Vector3 _center;

        public:
            /**
             * @brief Construct a new Box Collider object
             * 
             * @param center 
             * @param width (X axis)
             * @param depth (Y axis)
             * @param height (Z axis)
             */
            BoxCollider(const Vector3 center, double width, double depth, double height);

            /**
             * @brief Destroy the Box Collider object
             * 
             */
            ~BoxCollider() = default;

            /**
             * @brief access to point number i
             * 
             * @param i 
             * @return const glm::vec3& 
             */
            const Vector3 &operator[](int i) const;

            /**
             * @brief Tell if the point is present
             * 
             * @return true 
             * @return false 
             */
            bool hasPoint(const Vector3 &) const;

            /**
             * @brief tell if this object contains a point approximatively close to p
             * 
             * @param p point to search
             * @param eps approximation, sphere when we can look for this point
             * @return true 
             * @return false 
             */
            bool contains(const Vector3 &p, double eps = 1E-3) const;

            /**
             * @brief Get the Nb Points object
             * 
             * @return int 
             */
            int getNbPoints() const;

            /**
             * @brief Set the Rotation object and update points
             * 
             * @param v 
             */
            void setRotation(const Vector3 v);

            /**
             * @brief Get the Rotation object
             * 
             * @return const Vector3 
             */
            const Vector3 getRotation() const;

            /**
             * @brief Get the relative Axis of the object
             * 
             * @return std::vector<Vector3> 
             */
            std::vector<Vector3> getAxis() const;

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
            static void rotate(Vector3 points[], unsigned int size, const Vector3 &center, double alpha, double beta, double gamma);
            static void rotate(Vector3 points[], unsigned int size, const Vector3 &center, const Vector3 &rotation);
        };

        std::ostream &operator<<(std::ostream &oss, const BoxCollider &b);
    }
}