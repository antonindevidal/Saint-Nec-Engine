#include "util.hpp"
// #include "../architecture/util.hpp"

namespace sne::physics
{
    glm::vec3 getNormal(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return glm::cross(v1, v2);
    }

    bool areDisjoint(double x1_min, double x1_max, double x2_min, double x2_max)
    {
        // Returns true if: [x1_min ; x1_max] ∩ [x2_min; x2_max] = ∅
        return x1_max < x2_min || x2_max < x1_min;
    }

    double dot(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        // If one of the vector norm is 1 then it's a simple projection
        return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    }

    bool intersect(const BoxCollider &boxe1, const BoxCollider &boxe2, const glm::vec3 &axis)
    {
        double boxe1_min = dot(axis, boxe1[0]),
               boxe1_max = boxe1_min,
               boxe2_min = dot(axis, boxe2[0]),
               boxe2_max = boxe2_min;

        for (int i = 1; i < boxe1.getNbPoints(); i++)
        {
            double boxe1_projection = dot(axis, boxe1[i]),
                   boxe2_projection = dot(axis, boxe2[i]);

            boxe1_min = (boxe1_min < boxe1_projection) ? boxe1_min : boxe1_projection;
            boxe1_max = (boxe1_max > boxe1_projection) ? boxe1_max : boxe1_projection;
            boxe2_min = (boxe2_min < boxe2_projection) ? boxe2_min : boxe2_projection;
            boxe2_max = (boxe2_max > boxe2_projection) ? boxe2_max : boxe2_projection;
        }

        return !areDisjoint(boxe1_min, boxe1_max, boxe2_min, boxe2_max);
    }

    bool intersect(const SphereCollider &sphere1, const SphereCollider &sphere2, const glm::vec3 &axis)
    {
        (void)axis;
        double distance = norm(sphere1.getCenter() - sphere2.getCenter());

        return distance > (sphere1.getRadius() + sphere2.getRadius());
    }

    bool intersect(const SphereCollider &sphere, const BoxCollider &boxe, const glm::vec3 &axis)
    {
        double boxe_min = dot(axis, boxe[0]),
               boxe_max = boxe_min,
               sphere_min = dot(axis, sphere.getCenter()) - sphere.getRadius(),
               sphere_max = dot(axis, sphere.getCenter()) + sphere.getRadius();

        for (int i = 1; i < boxe.getNbPoints(); i++)
        {
            double boxe_projection = dot(axis, boxe[i]);

            boxe_min = (boxe_min < boxe_projection) ? boxe_min : boxe_projection;
            boxe_max = (boxe_max > boxe_projection) ? boxe_max : boxe_projection;
        }

        return !areDisjoint(boxe_min, boxe_max, sphere_min, sphere_max);
    }

    bool intersect(const BoxCollider &boxe, const SphereCollider &sphere, const glm::vec3 &axis)
    {
        return intersect(sphere, boxe, axis);
    }

    std::vector<Minkowski> minkowskiDifference(const BoxCollider &boxe1, const BoxCollider &boxe2)
    {
        std::vector<Minkowski> v;

        for (int i = 0; i < boxe1.getNbPoints(); i++)
        {
            for (int j = 0; j < boxe2.getNbPoints(); j++)
            {
                v.push_back(Minkowski{boxe1[i], boxe2[j]});
            }
        }

        std::sort(v.begin(), v.end(), [](const Minkowski &p1, const Minkowski &p2)
                  { return p1.getDistance() < p2.getDistance(); });

        return v;
    }

    std::vector<Minkowski> minkowskiDifference(const BoxCollider &boxe, const SphereCollider &sphere)
    {
        std::vector<Minkowski> v;

        for (int i = 0; i < boxe.getNbPoints(); i++)
        {
            v.push_back(Minkowski{boxe[i], sphere.getCenter()});
        }

        std::sort(v.begin(), v.end(), [](const Minkowski &p1, const Minkowski &p2)
                  { return p1.getDistance() < p2.getDistance(); });

        return v;
    }

    glm::vec3 collisionNormal(const BoxCollider &boxeA, const BoxCollider &boxeB)
    {
        std::vector<Minkowski> v = minkowskiDifference(boxeA, boxeB);
        glm::vec3 pointA1 = v[0].getPointA(),
                  pointA2 = v[1].getPointA(),
                  pointA3 = v[2].getPointA(),
                  pointA4 = v[3].getPointA();

        // Get directions
        glm::vec3 axis1 = pointA2 - pointA1,
                  axis2 = pointA3 - pointA1,
                  axis3 = pointA4 - pointA1;

        // Normalize
        axis1 = (norm(axis1) == 0) ? axis1 : axis1 / norm(axis1);
        axis2 = (norm(axis2) == 0) ? axis2 : axis2 / norm(axis2);
        axis3 = (norm(axis3) == 0) ? axis3 : axis3 / norm(axis3);

        std::cout << "LAaaaaaaaaaaa\n";
        std::cout << " axis 1:" << axis1 << "\n";
        std::cout << " axis 1:" << axis2 << "\n";
        std::cout << " axis 1:" << axis3 << "\n";
        std::cout << " point3 1:" << pointA1 << "\n";
        std::cout << " point3 1:" << pointA2 << "\n";
        std::cout << " point3 1:" << pointA3 << "\n";
        std::cout << " point3 1:" << pointA4 << "\n";
        // Get opposite direction
        return axis1 + axis2 + axis3;

        // TO UPDATE, 2 axis for each ?
        /*glm::vec3 pointB1 = v[0].getPointB(),
            pointB2 = v[1].getPointB(),
            pointB3 = v[2].getPointB(),
            pointB4 = v[3].getPointB();*/
    }

    glm::vec3 collisionNormal(const BoxCollider &boxe, const SphereCollider &sphere)
    {
        std::vector<Minkowski> v = minkowskiDifference(boxe, sphere);
        glm::vec3 pointA1 = v[0].getPointA(),
                  pointA2 = v[1].getPointA(),
                  pointA3 = v[2].getPointA(),
                  pointA4 = v[3].getPointA();

        // Get directions
        glm::vec3 axis1 = pointA2 - pointA1,
                  axis2 = pointA3 - pointA1,
                  axis3 = pointA4 - pointA1;

        // Normalize
        axis1 /= norm(axis1);
        axis2 /= norm(axis2);
        axis3 /= norm(axis3);

        // Get opposite direction
        return axis1 + axis2 + axis3;
    }

    glm::vec3 collisionNormal(const SphereCollider &sphere, const BoxCollider &boxe)
    {
        return collisionNormal(boxe, sphere);
    }

    glm::vec3 collisionNormal(const SphereCollider &sphere1, const SphereCollider &sphere2)
    {
        return sphere2.getCenter() - sphere1.getCenter();
    }

    glm::vec3 support(const Collider &shape1, const Collider &shape2, const glm::vec3 &axis)
    {
        // get points on the edge of the shapes in opposite directions
        glm::vec3 p1 = shape1.farthestPoint(axis);
        glm::vec3 p2 = shape2.farthestPoint(-axis);

        // Minkowski Difference
        glm::vec3 p3 = p1 - p2;

        return p3;
    }

    // bool gjk(const Collider &A, const Collider &B)
    // {
    //     Simplex simplex;
    //     glm::vec3 direction = B.getCenter() - A.getCenter();

    //     std::cout << "ma direction:" << direction << "\n";
    //     std::cout << "jinsere: " << support(A, B, direction) << "\n";
    //     simplex.push_front(support(A, B, direction));

    //     direction = -direction;

    //     // int MAX = 100;
    //     int i = 0;
    //     while (i < 100)
    //     {
    //         i++;
    //         std::cout << "ma direction:" << direction << "\n";
    //         glm::vec3 newPoint = support(A, B, direction);

    //         if (dot(newPoint, direction) < 0.0f)
    //         {
    //             std::cout << "!!!!\n";
    //             return false; // No collision
    //         }

    //         std::cout << "jinsere: " << newPoint << "\n";
    //         if(simplex.isPresent(newPoint))
    //             return false; // loop
            
    //         simplex.push_front(newPoint);

    //         if (NextSimplex(simplex, direction))
    //         {
    //             std::cout << "???????????????\n";
    //             return true; // Collision detected
    //         }

    //         switch (simplex.INFO)
    //         {
    //         case MANAGECOLLISION::COLLIDE:
    //             return true;
    //         case MANAGECOLLISION::DONTCOLLIDE:
    //             return false;
    //         case MANAGECOLLISION::OVERLOOP:
    //             return false;
    //         case MANAGECOLLISION::CHECKNEXTPOINT:
    //         {
    //             newPoint = support(A, B, direction);
    //             std::cout << "FATIGUEEEE:" << norm(-simplex[0]) << " - " << norm(newPoint - simplex[0]) << "\n\n\n";
    //             if (norm(-simplex[0]) < norm(newPoint - simplex[0]))
    //             {
    //                 return true;
    //             }
    //         }
    //         default:
    //             break;
    //         }

    //         simplex.INFO = MANAGECOLLISION::NOTHING;
    //     }

    //     return true;
    // }

    // bool gjk(const SphereCollider &A, const SphereCollider &B)
    // {

    //     float AB = glm::distance(A.getCenter(), B.getCenter());

    //     return AB < (A.getRadius() + B.getRadius());
    // }

    // bool sameDirection(const vec3 &v1, const vec3 &v2)
    // {
    //     return dot(v1, v2) > 0;
    // }

    // bool line(Simplex &simplex, vec3 &direction)
    // {
    //     vec3 a = simplex[0];
    //     vec3 b = simplex[1];

    //     vec3 ab = b - a,
    //          ao = -a;

    //     vec3 newDirection = glm::cross(ab, ao);

    //     if (norm(newDirection) == 0)
    //     {
    //         // Colineaire
    //         newDirection = {ab[1], ab[0], 0};
    //         if (sameDirection(ab, ao))
    //         {
    //             simplex.INFO = MANAGECOLLISION::CHECKNEXTPOINT;
    //             std::cout << "tulululut:" << norm(ab) << " - " << norm(ao) << "\n\n\n";
    //             if (norm(ab) >= norm(ao))
    //             {
    //                 std::cout << "pinpompimpom\n";
    //                 simplex.INFO = MANAGECOLLISION::COLLIDE;
    //             }
    //             direction = newDirection;
    //             return false;
    //         }
    //     }

    //     std::cout << "same direction ?" << newDirection << "\n";
    //     newDirection = glm::cross(newDirection, ao);
    //     std::cout << "new: " << newDirection << "-" << direction << "\n";

    //     // // case direction are the same as before: we pass through origin
    //     if (sameDirection(direction, newDirection))
    //     {
    //         std::cout << "same direction !\n";
    //     }

    //     direction = newDirection;
    //     std::cout << "new: " << newDirection << "-" << direction << "\n\n\n";

    //     return false;
    // }

    // bool triangle(Simplex &simplex, vec3 &direction)
    // {
    //     vec3 a = simplex[0],
    //          b = simplex[1],
    //          c = simplex[2];

    //     vec3 ab = b - a,
    //          ac = c - a,
    //          ao = -a;

    //     vec3 abNormal = glm::cross(glm::cross(ab, ao), ab),
    //          acNormal = glm::cross(glm::cross(ac, ao), ac);

    //     if (dot(abNormal, ao) > 0)
    //     {
    //         if (sameDirection(direction, abNormal))
    //         {
    //             std::cout << "same direction !\n";
    //         }
    //         direction = abNormal;
    //         return false;
    //     }
    //     else if (dot(acNormal, ao) > 0)
    //     {
    //         if (sameDirection(direction, acNormal))
    //         {
    //             std::cout << "same direction !\n";
    //         }
    //         direction = acNormal;
    //         return false;
    //     }

    //     return true;
    // }

    // bool tetrahedron(Simplex &simplex, vec3 &direction)
    // {

    //     // We check the 4 faces of the tetrahedron
    //     // We are looking for a possible new point
    //     // closer to origin
    //     float maxDot = 0;
    //     for (int i = 0; i < 4; i++)
    //     {
    //         vec3 a = simplex[i],
    //              b = simplex[(i + 1) % 4],
    //              c = simplex[(i + 2) % 4],
    //              ao = -a,
    //              ab = b - a;

    //         vec3 n = cross(ab, c - a);
    //         std::cout << "JERENTRE!!! - " << dot(ao, n) << " - " << norm(n) << "\n";
    //         maxDot = (maxDot < norm(n)) ? norm(b) : maxDot;
    //         if (norm(n) == 0)
    //         {
    //             // AB and AC colineaire
    //             n = {ab[1], ab[0], 0};
    //         }

    //         if (dot(ao, n) > 0)
    //         {
    //             // We remove the point wich is not contains by the closest face
    //             simplex.remove((i + 3) % 4);
    //             direction = n;
    //             return false;
    //         }
    //     }

    //     return true;
    // }

    // bool NextSimplex(Simplex &simplex, glm::vec3 &direction)
    // {
    //     switch (simplex.size())
    //     {
    //     case 2:
    //         return line(simplex, direction);
    //     case 3:
    //         return triangle(simplex, direction);
    //     case 4:
    //         return tetrahedron(simplex, direction);
    //     }

    //     return false;
    // }


    bool gjk(const Collider &coll1, const Collider &coll2)
    {
        vec3 a, b, c, d;                           // Simplex, easier this way without class
        vec3 search_dir = coll1.getCenter() - coll2.getCenter();

        c = support(coll1, coll2, search_dir);
        search_dir = -c; // search in direction of origin

        b = support(coll1, coll2, search_dir);
        
        if (dot(b, search_dir) < 0)
        {
            // Origin is not contianed
            return false;
        } 

        search_dir = cross(cross(c - b, -b), c - b); //get normal to line (sens of origin)
        
        if (search_dir == vec3(0, 0, 0))
        { 
            // origin is on this line segment
            search_dir = cross(c - b, vec3(1, 0, 0)); // normal with x-axis
            if (search_dir == vec3(0, 0, 0))
                search_dir = cross(c - b, vec3(0, 0, -1)); // normal with z-axis
        }

        int simp_dim = 2;

        for (int iterations = 0; iterations < GJK_MAX_NUM_ITERATIONS; iterations++)
        {
            a = support(coll1, coll2, search_dir);
            if (dot(a, search_dir) < 0)
            {
                // origin not contained
                return false;
            }

            simp_dim++;
            if (simp_dim == 3)
            {
                update_simplex3(a, b, c, d, simp_dim, search_dir);
            }
            else if (update_simplex4(a, b, c, d, simp_dim, search_dir))
            {
                return true;
            }
        } 
        return false;
    }

    // Triangle case
    void update_simplex3(vec3 &a, vec3 &b, vec3 &c, vec3 &d, int &simp_dim, vec3 &search_dir)
    {
        /* Required winding order:
        //  b
        //  | \
        //  |   \
        //  |    a
        //  |   /
        //  | /
        //  c
        */
        vec3 n = cross(b - a, c - a); // triangle's normal
        vec3 AO = -a;                 // direction to origin

        // Determine which feature is closest to origin, make that the new simplex

        simp_dim = 2;
        if (dot(cross(b - a, n), AO) > 0)
        { // Closest to edge AB
            c = a;
            // simp_dim = 2;
            search_dir = cross(cross(b - a, AO), b - a);
            return;
        }
        if (dot(cross(n, c - a), AO) > 0)
        { // Closest to edge AC
            b = a;
            // simp_dim = 2;
            search_dir = cross(cross(c - a, AO), c - a);
            return;
        }

        simp_dim = 3;
        if (dot(n, AO) > 0)
        { // Above triangle
            d = c;
            c = b;
            b = a;
            // simp_dim = 3;
            search_dir = n;
            return;
        }
        // else //Below triangle
        d = b;
        b = a;
        // simp_dim = 3;
        search_dir = -n;
        return;
    }

    // Tetrahedral case
    bool update_simplex4(vec3 &a, vec3 &b, vec3 &c, vec3 &d, int &simp_dim, vec3 &search_dir)
    {
        // a is the summit of the pyramid and BCD is the base
        // We know a priori that origin is above BCD and below a

        // Get normals of three new faces
        vec3 ABC = cross(b - a, c - a);
        vec3 ACD = cross(c - a, d - a);
        vec3 ADB = cross(d - a, b - a);

        vec3 AO = -a; // dir to origin
        simp_dim = 3; // hoisting this just cause

        if (dot(ABC, AO) > 0)
        { // In front of ABC
            d = c;
            c = b;
            b = a;
            search_dir = ABC;
            return false;
        }
        if (dot(ACD, AO) > 0)
        { // In front of ACD
            b = a;
            search_dir = ACD;
            return false;
        }
        if (dot(ADB, AO) > 0)
        { // In front of ADB
            c = d;
            d = b;
            b = a;
            search_dir = ADB;
            return false;
        }

        // else inside tetrahedron; enclosed!
        return true;
    }

}