#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "triangle.h"
#include "lightCol.h"



int main() {

    // World
    hittable_list world;

    // Now I need to 
    // 1. The ability to ray trace polygons
    // 2. The ability to handle a single shadow ray per intersection
    // 3. The ability to trace reflection rays at intersections.


    //world.add(make_shared<sphere>(point3(0,0,-1), 0.5, vec3(1,0,1)));
    //world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    //purple Sphere
    //auto purpleLight = lightCol(0.8, 0.1, 0.3, vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), 4.0);





    // ////////////////////////////////////////////////////RAY2FIRSTIMAGE///////////////////////////////////////////////////////////////////////

    // auto triLight = lightCol(0.9, 1.0, 0.1, vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 1.0), 4.0, 1);
    // //tri test
    // world.add(make_shared<triangle>(point3(0.0, -0.7, -0.5), point3(1.0, 0.4, -1.0), point3(0.0, -0.7, -1.5), triLight));

    // auto triLight2 = lightCol(0.9, 1.0, 0.1, vec3(1.0, 1.0, 0.0), vec3(1.0, 1.0, 1.0), 4.0, 1);
    // //tri test
    // world.add(make_shared<triangle>(point3(0.0, -0.7, -0.5), point3(0.0, -0.7, -1.5), point3(-1.0, 0.4, -1.0), triLight2));


    // // FIRST IMAGE SPHERE
    // auto firstLight = lightCol(0.0, 0.1, 0.1, vec3(.75, .75, .75), vec3(1.0, 1.0, 1.0), 10.0, 1);
    // world.add(make_shared<sphere>(point3(0.0, 0.3, -1.0), 0.25, firstLight));


    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






    ///////////////////////////////////////////////////RAY2SECONDIMAGE///////////////////////////////////////////////////////////////////////
    //white sphere
    auto whiteLight = lightCol(0.8, 0.1, 0.3, vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), 4.0, 1, 0.0);
    world.add(make_shared<sphere>(point3(0.5, 0.0, -0.15), 0.05, whiteLight));

    // red sphere
    auto redLight = lightCol(0.8, 0.8, 0.1, vec3(1.0, 0.0, 0.0), vec3(0.5, 1.0, 0.5), 32.0, 1, 0.0);
    world.add(make_shared<sphere>(point3(0.3, 0.0, -0.1), 0.08, redLight));

    // green sphere
    auto greenLight = lightCol(0.7, 0.5, 0.1, vec3(0.0, 1.0, 0.0), vec3(0.5, 1.0, 0.5), 64.0, 1, 0.0);
    world.add(make_shared<sphere>(point3(-0.6, 0.0, 0.0), 0.3, greenLight));

    // reflect sphere
    auto reflectLight = lightCol(0.0, 0.1, 0.1, vec3(0.75, 0.75, 0.75), vec3(1.0, 1.0, 1.0), 10.0, 1, 0.9);
    world.add(make_shared<sphere>(point3(0.1, -0.55, 0.25), 0.3, reflectLight));


    auto blueTri = lightCol(0.9, 0.9, 0.1, vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 1.0), 32.0, 1, 0.0);
    //tri test
    world.add(make_shared<triangle>(point3(0.3, -0.3, -0.4), point3(0.0, 0.3, -1.0), point3(-0.3, -0.3, 0.2), blueTri));

    auto yellowTri = lightCol(0.9, 0.5, 0.1, vec3(1.0, 1.0, 0.0), vec3(1.0, 1.0, 1.0), 4.0, 1, 0.0);
    //tri test
    world.add(make_shared<triangle>(point3(-0.2, 0.1, 0.1), point3(-0.2, -0.5, 0.2), point3(-0.2, 0.1, -0.3), yellowTri));


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








    // //white sphere
    // auto whiteLight = lightCol(0.8, 0.1, 0.3, vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), 4.0, 1);
    // world.add(make_shared<sphere>(point3(0.45, 0.0, -0.15), 0.15, whiteLight));

    // // red sphere
    // auto redLight = lightCol(0.6, 0.3, 0.1, vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), 32.0, 1);
    // world.add(make_shared<sphere>(point3(0.0, 0.0, -0.1), 0.2, redLight));

    // // red sphere
    // auto greenLight = lightCol(0.7, 0.2, 0.1, vec3(0.0, 1.0, 0.0), vec3(0.5, 1.0, 0.5), 64.0, 1);
    // world.add(make_shared<sphere>(point3(-0.6, 0.0, 0.0), 0.3, greenLight));

    // // blue sphere
    // auto blueLight = lightCol(0.9, 0.0, 0.1, vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 1.0), 16.0, 1);
    // world.add(make_shared<sphere>(point3(0.0, -10000.5, 0.0), 10000.0, blueLight));






    // //Sun
    // auto sunLight = lightCol(1, 0, 0, vec3(1, 0.7, 0), vec3(0, 0, 0), 1.0, 1.0);
    // world.add(make_shared<sphere>(point3(-75, 17, 0.0), 80, sunLight));

    // //Mercury
    // auto mercLight = lightCol(0.8, 0.1, 0.3, vec3(.9, .20, .20), vec3(1.0, 1.0, 1.0), 4.0, 0);
    // world.add(make_shared<sphere>(point3(0.0, 0.0, 0.0), 0.03, mercLight));

    // //Venus
    // auto venLight = lightCol(0.8, 0.1, 0.3, vec3(.63, .52, .07), vec3(1.0, 1.0, 1.0), 4.0, 0);
    // world.add(make_shared<sphere>(point3(0.2, 0.0, 0.0), 0.06, venLight));

    // //Earth
    // auto earthLight = lightCol(0.8, 0.1, 0.3, vec3(.25, .42, .88), vec3(1.0, 1.0, 1.0), 4.0, 0);
    // world.add(make_shared<sphere>(point3(0.4, 0.0, 0.0), 0.063, earthLight));

    // //Moon
    // auto moonLight = lightCol(0.8, 0.1, 0.3, vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), 4.0, 0);
    // world.add(make_shared<sphere>(point3(0.49, 0.055, 0.0), 0.021, moonLight));

    // //Mars
    // auto marsLight = lightCol(0.8, 0.1, 0.3, vec3(.75, .25, .07), vec3(1.0, 1.0, 1.0), 4.0, 0);
    // world.add(make_shared<sphere>(point3(0.65, 0.0, 0.0), 0.055, marsLight));

    // //Jupiter
    // auto jupiterLight = lightCol(0.8, 0.1, 0.3, vec3(.97, .86, .71), vec3(1.0, 1.0, 1.0), 4.0, 0);
    // world.add(make_shared<sphere>(point3(1.2, 0.0, 0.0), 0.3, jupiterLight));

    // // red sphere
    // auto redLight = lightCol(0.6, 0.3, 0.1, vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), 32.0);
    // world.add(make_shared<sphere>(point3(0.0, 0.0, -0.1), 0.2, redLight));

    // // red sphere6
    // auto greenLight = lightCol(0.7, 0.2, 0.1, vec3(0.0, 1.0, 0.0), vec3(0.5, 1.0, 0.5), 64.0);
    // world.add(make_shared<sphere>(point3(-0.6, 0.0, 0.0), 0.3, greenLight));

    // // blue sphere
    // auto blueLight = lightCol(0.9, 0.0, 0.1, vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 1.0), 16.0);
    // world.add(make_shared<sphere>(point3(0.0, -10000.5, 0.0), 10000.0, blueLight));





    

    camera cam;

    cam.aspect_ratio = 1.77;
    cam.image_width = 1000;

    cam.render(world);
}