#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "lightCol.h"


class sphere : public hittable {
    public:
        sphere(const point3& center, double radius, const lightCol& lc) : center(center), radius(std::fmax(0,radius)), lc(lc) {}

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
            rec.refl = lc.refl;

            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }



    private:
        point3 center;
        double radius;
        lightCol lc;
};

#endif