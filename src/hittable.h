#ifndef HITTABLE_H
#define HITTABLE_H



class hit_record {
    public:
        point3 p;
        vec3 normal;
        vec3 Od;
        vec3 Os;
        double t, Kd, Ks, Ka, Kgls, sun, refl;
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outward_normal) {
            // Sets the hit record normal vector
            // NOTE: the parameter `outward_normal` is assumed to have unit length.

            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};


#endif