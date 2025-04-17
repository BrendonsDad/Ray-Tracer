#ifndef LIGHT_COL
#define LIGHT_COL

#include "vec3.h"



class lightCol {
  public:

    double Kd, Ks, Ka, Kgls, refl;
    double sun = 0.0;
    vec3 Od, Os;
    
    lightCol(double Kd, double Ks, double Ka, vec3& Od, vec3& Os, double Kgls, double sun, double refl) : Kd(Kd),  Ks(Ks), Ka(Ka), Od(Od), Os(Os), Kgls(Kgls), sun(sun), refl(refl){}



};

#endif