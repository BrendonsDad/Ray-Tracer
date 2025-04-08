#---------------------------------------------------------------------------
# CMake Build Configuration for the ray tracer
#
#---------------------------------------------------------------------------
cmake_minimum_required( VERSION 3.1.0...3.27.0 )

project ( RTWeekend LANGUAGES CXX )

# Set to c++11
set ( CMAKE_CXX_STANDARD          11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

# Source
set ( EXTERNAL
  src/external/stb_image.h
)

set ( SOURCE_ONE_WEEKEND 
  src/main.cpp
  src/color.h
  src/vec3.h
  src/ray.h
  src/hittable.h
  src/sphere.h
  src/hittable_list.h
  src/rtweekend.h
  src/interval.h
  src/camera.h
  src/lightCol.h
  src/triangle.h

)

include_directories(src)

# Executables
add_executable(inOneWeekend         ${EXTERNAL} ${SOURCE_ONE_WEEKEND})