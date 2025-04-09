#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "lightCol.h"
#include "interval.h"
#include "ray.h"


class triangle : public hittable {
    public:
        triangle(const point3& v0, const point3& v1, const point3& v2,  const lightCol& lc) : v0(v0), v1(v1), v2(v2), lc(lc) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {

            const float EPSILON = 1e-8;

            /*
                PSUDOCODE
                Vec3f edge0 = v1 - v0; //first edge of triangle
                Vec3f edge1 = v2 - v1; //second edge of triangle
                Vec3f edge2 = v0 - v2; //third edge of triangle

                Vec3f C0 = P - v0; //vector from v0 inter point
                Vec3f C1 = P - v1; //vector from v1 inter point
                Vec3f C2 = P - v2; //vector from v2 inter point

                if (dotProduct(N, crossProduct(edge0, C0)) > 0 &&
                    dotProduct(N, crossProduct(edge1, C1)) > 0 &&
                    dotProduct(N, crossProduct(edge2, C2)) > 0)
                    
                    return true; // P is inside the triangle
            */

            vec3 edge1 = v1 - v0;
            vec3 edge2 = v2 - v0;

            vec3 h = cross(r.direction(), edge2);
            float a = dot(edge1, h);

            if (fabs(a) < EPSILON) return false; // Ray is parallel to triangle

            float f = 1.0 / a;
            vec3 s = r.origin() - v0;
            float u = f * dot(s, h);
            if (u < 0.0 || u > 1.0) return false;

            vec3 q = cross(s, edge1);
            float v = f * dot(r.direction(), q);
            if (v < 0.0 || u + v > 1.0) return false;

            float t = f * dot(edge2, q);
            if (!ray_t.surrounds(t)) return false;

            // Compute the intersection point
            rec.t = t;
            rec.p = r.at(t);

            //surface normal
            vec3 normal = unit_vector(cross(edge1, edge2));
            rec.set_face_normal(r, normal);

            rec.Od = lc.Od;
            rec.Kd = lc.Kd;
            rec.Ka = lc.Ka;
            rec.Ks = lc.Ks;
            rec.Os = lc.Os;
            rec.Kgls = lc.Kgls;
            rec.sun = lc.sun;

            return true;



           

        //    vec3 edge0 = v1 - v0; //first edge of triangle
        //    vec3 edge1 = v2 - v1; //second edge of triangle
        //    vec3 edge2 = v0 - v2; //third edge of triangle

        //    vec3 C0 = P - v0; //vector from v0 inter point
        //    vec3 C1 = P - v1; //vector from v1 inter point
        //    vec3 C2 = P - v2; //vector from v2 inter point

        //    vec3 N = unit_vector(r.direction());

        //    if (dot(N, cross(edge0, C0)) > 0 &&
        //        dot(N, cross(edge1, C1)) > 0 &&
        //        dot(N, cross(edge0, C0)) > 0)

        //        // rec.t = root;
        //         rec.Od = lc.Od;
        //         rec.Os = lc.Os;
        //         rec.Kd = lc.Kd;
        //         rec.Ka = lc.Ka;
        //         rec.Ks = lc.Ks;
        //         rec.Kgls = lc.Kgls;
        //         rec.sun = lc.sun;

        //         rec.p = r.at(rec.t);

        //        return true; // P is inside the triagnle

            
        //     // vec3 outward_normal = (rec.p - center) / radius;
        //     // rec.set_face_normal(r, outward_normal);

        //     return false;
        }



    private:
        point3 v0;
        point3 v1;
        point3 v2;
        lightCol lc;
};

#endif