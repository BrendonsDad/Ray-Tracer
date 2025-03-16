#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "lightCol.h"


class triangle : public hittable {
    public:
        triangle(const point3& triP1, const point3& triP2, const point3& triP3,  const lightCol& lc) : triP1(triP1), triP2(triP2), triP3(triP3), lc(lc) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius*radius;

            auto discriminant = h*h - a*c;
            if (discriminant < 0)
                return false;

            auto sqrtd = std::sqrt(discriminant);

            // Find the nearest root that lies in the acceptable range.
            auto root = (h - sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                root = (h + sqrtd) / a;
                if (!ray_t.surrounds(root))
                    return false;
            }

            rec.t = root;
            rec.Od = lc.Od;
            rec.Os = lc.Os;
            rec.Kd = lc.Kd;
            rec.Ka = lc.Ka;
            rec.Ks = lc.Ks;
            rec.Kgls = lc.Kgls;
            rec.sun = lc.sun;

            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }



    private:
        point3 triP1;
        point3 triP2;
        point3 triP3;
        double radius;
        lightCol lc;
};

#endif