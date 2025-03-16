#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include <cmath>


class camera {

    public:
        double aspect_ratio = 16/9; // Ratio of image width over height
        int image_width     = 100; // Render image width in pixel count

        void render(const hittable& world) {
            initialize();

            // Render

            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++) {
                    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                    auto ray_direction = pixel_center - center;
                    ray r(center, ray_direction);

                    color pixel_color = ray_color(r, world);
                    write_color(std::cout, pixel_color);
                }
            }

            std::clog << "\rDone.                   \n";
            
        }

    private:
        int    image_height;    // Rendered image height
        point3 center;          // Camera center
        point3 pixel00_loc;     // Location of pixel 0, 0
        vec3   pixel_delta_u;   // Offset to pixel to the right
        vec3   pixel_delta_v;   // Offset to pixel below

        void initialize() {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            center = point3(0, 0, 1);

            //Determine viewport dimensions.
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width)/image_height);

            // Calculate the vectors across the horizontal and down the vertical viewport edges.
            auto viewport_u = vec3(viewport_width, 0, 0);
            auto viewport_v = vec3(0, -viewport_height, 0);

            // Calculate the horizontal and vertical delta vectors from pixel to pixel. 
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // Calculate the location of the upper left pixel to pixel.
            auto viewport_upper_left = 
                    center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        }

        color ray_color(const ray& r, const hittable& world) const {
            hit_record rec;



            if (world.hit(r, interval(0, infinity), rec)) {
                /////---------------------------------------------------------------------/////
                // IF A HIT, DO AUBURYS LIGHT CODE                                           //
                /////---------------------------------------------------------------------/////

                // light color
                auto lightColor = vec3(1.0, 1.0, 1.0);
                // Ambient light
                auto ambientl =  vec3(0.1, 0.1, 0.1);
                // Direction to light
                auto L = vec3(1.0, 1.0, 1.0);
                if (rec.sun != 1.0) {
                    L = vec3(-1.0, 0.50, .250);
                }

                double kd = rec.Kd;
                double ks = rec.Ks;
                double ka = rec.Ka;
                auto Od = rec.Od; 
                auto Os = rec.Os;
                double Kgls = rec.Kgls;

                auto ambient = ka*lightColor*Od;
                auto nldot = dot(unit_vector(rec.normal), L);
                double dotmax;
                if (nldot < 0) {
                    dotmax = 0;
                } else {
                    dotmax = nldot;
                }
                auto diffuse = kd*lightColor*Od*dotmax;



                //Last one is specular, we need to define what r is and we need to define what V is. 
                auto R = unit_vector(2*(dot(L, unit_vector(rec.normal)))*(rec.normal-L));
                auto V = -1*unit_vector(r.direction());
                //V = unit_vector(V);
                double VRDot = dot(V, R);
                double VRMax;
                vec3 specular;


                if (VRDot < 0) {
                    VRMax = 0;
                    specular = vec3(0,0,0);
                } else {

                    VRMax = pow(VRDot, Kgls);
                    // VRMax = VRDot;
                    // for (int i = 0; i < Kgls; i++) {
                    //     VRMax = VRMax * VRDot;
                    // }
                    specular = ks*lightColor*Os*VRMax;
                }

                auto finalcolor = ambient + diffuse + specular;


                // auto purple = vec3(1, 0, 1);
                // return purple;
                // return 0.5 * (rec.normal + color(1, 1, 1));
                double maxX, maxY, maxZ;
                if (finalcolor.x() > 1) {
                    maxX = 1;
                } else {
                    maxX = finalcolor.x();
                }

                if (finalcolor.y() > 1) {
                    maxY = 1;
                } else {
                    maxY = finalcolor.y();
                }

                if (finalcolor.z() > 1) {
                    maxZ = 1;
                } else {
                    maxZ = finalcolor.z();
                }

                auto maxFinal = vec3(maxX, maxY, maxZ);

                return maxFinal;
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            //bg color
            auto bg = vec3(.2, .2, .2);
            return bg;//(1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
};

#endif