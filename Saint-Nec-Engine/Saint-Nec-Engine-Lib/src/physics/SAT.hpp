// #pragma once
// #include "BoxCollider.hpp"
// #include "SphereCollider.hpp"


// namespace sne
// {

//     namespace saintNecPhysics
//     {

//         class SATIllegalUseException : public std::exception
//         {

//         public:
//             const char* what() const noexcept override
//             {
//                 return "Illegal use of SAT algorithm";
//             }
//         };
//         /**
//          * @brief tell if: [x1_min ; x1_max] ∩ [x2_min; x2_max] = ∅
//          * 
//          * @param x1_min 
//          * @param x1_max 
//          * @param x2_min 
//          * @param x2_max 
//          * @return true 
//          * @return false 
//          */
//         bool areDisjoint(double x1_min, double x1_max, double x2_min, double x2_max);

//         /**
//          * @brief scalar product v1 . v2
//          * 
//          * @param v1 
//          * @param v2 
//          * @return double 
//          */
//         double dot(const Vector3 v1, const Vector3 v2);
        
//         /**
//          * @brief concatenation of v1 and v2 into an other vector
//          * 
//          * @param v1 
//          * @param v2 
//          * @return std::vector<Vector3> 
//          */
//         std::vector<Vector3> operator+(const std::vector<Vector3> v1, const std::vector<Vector3> v2);

//         /**
//          * @brief detect collision relating to Separate Axis Theorem algorithm
//          * SAT is usefull only for convexe objects
//          * 
//          * Theoreme:
//          * If there is any gap (one disjoint) on any axis then there is no collision
//          * 
//          * @return true if collision detected
//          * @return false if no collision detected
//          */
//         template <typename ColliderType1, typename ColliderType2>
//         bool hasSatCollision(const ColliderType1&, const ColliderType2&)
//         {
//             throw new SATIllegalUseException();
//         }
//         bool hasSATCollision(const BoxCollider &boxe1, const BoxCollider &boxe2);
//         bool hasSATCollision(const SphereCollider &sphere1, const SphereCollider &sphere2);
//         bool hasSATCollision(const BoxCollider &boxe, const SphereCollider &sphere);
//         bool hasSATCollision(const SphereCollider &sphere, const BoxCollider &boxe);
//     }
// }