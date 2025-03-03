#include <iostream>

int main() {

    // Image

    int image_width = 256;
    int image_heigt = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_heigt << "\n255\n";

    for (int j = 0; j < image_heigt; j++) {
        std::clog << "\rScanlines remaining: " << (image_heigt - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_heigt-1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);
            
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
            // Lets add a progress indicator

        }
    }

    std::clog << "\rDone.                   \n";
}