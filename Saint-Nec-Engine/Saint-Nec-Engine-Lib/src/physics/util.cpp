#include "util.hpp"

namespace sne::physics
{

    bool areDisjoint(float x1_min, float x1_max, float x2_min, float x2_max)
    {
        // Returns true if: [x1_min ; x1_max] ∩ [x2_min; x2_max] = ∅
        return x1_max < x2_min || x2_max < x1_min;
    }

    bool intersect(const BoxCollider &boxe1, const BoxCollider &boxe2, const glm::vec3 &axis)
    {
        float boxe1_min = dot(axis, boxe1[0]),
               boxe1_max = boxe1_min,
               boxe2_min = dot(axis, boxe2[0]),
               boxe2_max = boxe2_min;

        for (int i = 1; i < boxe1.getNbPoints(); i++)
        {
            float boxe1_projection = dot(axis, boxe1[i]),
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
        float distance = norm(sphere1.getCenter() - sphere2.getCenter());

        return distance < (sphere1.getRadius() + sphere2.getRadius());
    }

    bool intersect(const SphereCollider &sphere, const BoxCollider &boxe, const glm::vec3 &axis)
    {
        float boxe_min = dot(axis, boxe[0]),
               boxe_max = boxe_min,
               sphere_min = dot(axis, sphere.getCenter()) - sphere.getRadius(),
               sphere_max = dot(axis, sphere.getCenter()) + sphere.getRadius();

        for (int i = 1; i < boxe.getNbPoints(); i++)
        {
            float boxe_projection = dot(axis, boxe[i]);

            boxe_min = (boxe_min < boxe_projection) ? boxe_min : boxe_projection;
            boxe_max = (boxe_max > boxe_projection) ? boxe_max : boxe_projection;
        }

        return !areDisjoint(boxe_min, boxe_max, sphere_min, sphere_max);
    }

    bool intersect(const BoxCollider &boxe, const SphereCollider &sphere, const glm::vec3 &axis)
    {
        return intersect(sphere, boxe, axis);
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