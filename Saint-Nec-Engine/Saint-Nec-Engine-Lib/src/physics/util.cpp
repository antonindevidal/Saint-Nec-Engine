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


    bool gjk(const Collider &coll1, const Collider &coll2, glm::vec3 &normal)
    {
        glm::vec3 a, b, c, d;                           // Simplex, easier this way without class
        glm::vec3 search_dir = coll1.getCenter() - coll2.getCenter();

        c = support(coll1, coll2, search_dir);
        search_dir = -c; // search in direction of origin

        b = support(coll1, coll2, search_dir);
        
        if (dot(b, search_dir) < 0)
        {
            // Origin is not contianed
            return false;
        } 

        search_dir = cross(cross(c - b, -b), c - b); //get normal to line (sens of origin)
        
        if (search_dir == ORIGIN)
        { 
            // origin is on this line segment
            search_dir = cross(c - b, glm::vec3(1, 0, 0)); // normal with x-axis
            if (search_dir == glm::vec3(0, 0, 0))
                search_dir = cross(c - b, glm::vec3(0, 0, -1)); // normal with z-axis
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
                normal = EPA(a,b,c,d,coll1,coll2);
                return true;
            }
        } 
        return false;
    }

    // Triangle case
    void update_simplex3(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, glm::vec3 &d, int &simp_dim, glm::vec3 &search_dir)
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
        glm::vec3 n = cross(b - a, c - a); // triangle's normal
        glm::vec3 AO = -a;                 // direction to origin

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
    bool update_simplex4(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, glm::vec3 &d, int &simp_dim, glm::vec3 &search_dir)
    {
        // a is the summit of the pyramid and BCD is the base
        // We know a priori that origin is above BCD and below a

        // Get normals of three new faces
        glm::vec3 ABC = cross(b - a, c - a);
        glm::vec3 ACD = cross(c - a, d - a);
        glm::vec3 ADB = cross(d - a, b - a);

        glm::vec3 AO = -a; // dir to origin
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

    glm::vec3 EPA(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, const Collider &coll1, const Collider &coll2)
    {
        glm::vec3 faces[EPA_MAX_NUM_FACES][4]; // Array of faces, each with 3 vertices and a normal

        // std::cout << "Simplex found:\n";
        // std::cout << a << "\n" << b << "\n" << c << "\n" << d << "\n";

        // Init with final simplex from GJK
        faces[0][0] = a;
        faces[0][1] = b;
        faces[0][2] = c;
        faces[0][3] = glm::normalize(cross(b - a, c - a)); // ABC
        faces[1][0] = a;
        faces[1][1] = c;
        faces[1][2] = d;
        faces[1][3] = glm::normalize(cross(c - a, d - a)); // ACD
        faces[2][0] = a;
        faces[2][1] = d;
        faces[2][2] = b;
        faces[2][3] = glm::normalize(cross(d - a, b - a)); // ADB
        faces[3][0] = b;
        faces[3][1] = d;
        faces[3][2] = c;
        faces[3][3] = glm::normalize(cross(d - b, c - b)); // BDC

        int num_faces = 4;
        int closest_face;

        for (int iterations = 0; iterations < EPA_MAX_NUM_ITERATIONS; iterations++)
        {
            // Find face that's closest to origin
            float min_dist = dot(faces[0][0], faces[0][3]);
            closest_face = 0;
            for (int i = 1; i < num_faces; i++)
            {
                float dist = dot(faces[i][0], faces[i][3]);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    closest_face = i;
                }
            }

            // search normal to face that's closest to origin
            glm::vec3 search_dir = faces[closest_face][3];
            glm::vec3 p = support(coll1, coll2, search_dir);

            // std::cout << "ici" <<  min_dist << "\n";

            if (dot(p, search_dir) - min_dist < EPA_TOLERANCE)
            {
                // Convergence (new point is not significantly further from origin)
                return faces[closest_face][3] * glm::dot(p, search_dir); // dot vertex with normal to resolve collision along normal!
            }

            glm::vec3 loose_edges[EPA_MAX_NUM_LOOSE_EDGES][2]; // keep track of edges we need to fix after removing faces
            int num_loose_edges = 0;

            // Find all triangles that are facing p
            for (int i = 0; i < num_faces; i++)
            {
                if (dot(faces[i][3], p - faces[i][0]) > 0) // triangle i faces p, remove it
                {
                    // Add removed triangle's edges to loose edge list.
                    // If it's already there, remove it (both triangles it belonged to are gone)
                    for (int j = 0; j < 3; j++) // Three edges per face
                    {
                        glm::vec3 current_edge[2] = {faces[i][j], faces[i][(j + 1) % 3]};
                        bool found_edge = false;
                        for (int k = 0; k < num_loose_edges; k++) // Check if current edge is already in list
                        {
                            if (loose_edges[k][1] == current_edge[0] && loose_edges[k][0] == current_edge[1])
                            {
                                // Edge is already in the list, remove it
                                // THIS ASSUMES EDGE CAN ONLY BE SHARED BY 2 TRIANGLES (which should be true)
                                // THIS ALSO ASSUMES SHARED EDGE WILL BE REVERSED IN THE TRIANGLES (which
                                // should be true provided every triangle is wound CCW)
                                loose_edges[k][0] = loose_edges[num_loose_edges - 1][0]; // Overwrite current edge
                                loose_edges[k][1] = loose_edges[num_loose_edges - 1][1]; // with last edge in list
                                num_loose_edges--;
                                found_edge = true;
                                k = num_loose_edges; // exit loop because edge can only be shared once
                            }
                        } // endfor loose_edges

                        if (!found_edge)
                        { // add current edge to list
                            // assert(num_loose_edges<EPA_MAX_NUM_LOOSE_EDGES);
                            if (num_loose_edges >= EPA_MAX_NUM_LOOSE_EDGES)
                                break;
                            loose_edges[num_loose_edges][0] = current_edge[0];
                            loose_edges[num_loose_edges][1] = current_edge[1];
                            num_loose_edges++;
                        }
                    }

                    // Remove triangle i from list
                    faces[i][0] = faces[num_faces - 1][0];
                    faces[i][1] = faces[num_faces - 1][1];
                    faces[i][2] = faces[num_faces - 1][2];
                    faces[i][3] = faces[num_faces - 1][3];
                    num_faces--;
                    i--;
                } // endif p can see triangle i
            }     // endfor num_faces

            // Reconstruct polytope with p added
            for (int i = 0; i < num_loose_edges; i++)
            {
                // assert(num_faces<EPA_MAX_NUM_FACES);
                if (num_faces >= EPA_MAX_NUM_FACES)
                    break;
                faces[num_faces][0] = loose_edges[i][0];
                faces[num_faces][1] = loose_edges[i][1];
                faces[num_faces][2] = p;
                faces[num_faces][3] = glm::normalize(cross(loose_edges[i][0] - loose_edges[i][1], loose_edges[i][0] - p));

                // Check for wrong normal to maintain CCW winding
                float bias = 0.000001; // in case dot result is only slightly < 0 (because origin is on face)
                if (dot(faces[num_faces][0], faces[num_faces][3]) + bias < 0)
                {
                    glm::vec3 temp = faces[num_faces][0];
                    faces[num_faces][0] = faces[num_faces][1];
                    faces[num_faces][1] = temp;
                    faces[num_faces][3] = -faces[num_faces][3];
                }
                num_faces++;
            }
        } 

        printf("EPA did not converge\n");
        
        // Return most recent closest point
        return faces[closest_face][3] * glm::dot(faces[closest_face][0], faces[closest_face][3]);
    }
}