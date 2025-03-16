# 2. Output an Image

## 2.1 The PPM Image Format

Whenever you start a renderer, you need a way to see an image. The most straightforward way is to write it to a file. Always start with a plain text ppm file. 

There are some things to note in this code:
1. The pixels are written out in rows.
2. Every row of pixels is written out left to right
3. These rows are written out from top to bottom.
4. By convention, each of the red/green/blue components are represented internally by real valued variables that range from 0.0 to 1.0. These must be scaled to integer values between 0 and 255 before we print them out.
5. Red goes from fully off (black) to fully on (bright red) from left to right and green goes from fully off at the top (black) to fully on at the bottom (bright green). Adding red and green light together make yello so we should expect the bottom right corner to be yellow. 


## 2.2 Creating an image file

Becuase the file is written to the standard output stream, you'll need ot redirect it to an image file. Typically this is done from the command-line by using the > redirection operator.

On windows, you'd get the debug build from CMake running this command.

# 3. The vec3 Class
We will use the class vec3 for colors, lovations, directions, offsets, whatever. 

We use double here, but some ray tracers use float. double has greater precision and range but is twice the size compared to float. This effects memory conditions such as hardware shaders.

Now using our vec3 class, lets create a new color.h header file and define a utility function that writes a single pixels color out to the standard output stream

Now we can change our main to use both of these.

# 4. Rays, a simple Camera, and Background

### 4.1 The ray Class
The one thing that all ray tracers have is a ray class and a computation of what color is seen along a ray. Let's think aof a ray as a function P(t) = A +tb. Here P is a 3D position along a line in 3D. A is the ray origin and b is the ray direction. 

### 4.2 Sending Rays Into the Scene
Now we are ready to make a ray tracer. At its core, a ray tracer sends rays through pixels and computes the color seen in the direction of those rays. The involved steps are.

1. Calculate the ray from the "eye" through the pixel,
2. Determine which objects the ray intersects, and
3. Compute a coor for the closest intersection point. 

Always when first developing a ray tracer, get a simple camera for getting the code up and running. We will use a 16:9 aspect ratio becuase it is so common. 
width/height = 16/9 = 1.7778

In addition to setting up the pixel dimensions for the rendered image, we also need ot set up a vitual viewport thorugh which to pass our scene rays. The viewport is a vitual rectangle in the 3D world that contains the grid of image pixel locations. If pixels are spaced the same distance horzontally as they are vertically, the viewport that bounds them will have the same aspect ratio as the rendered image. The distance between two adjacent pixels is called the pixel spaceing and square pixels is the standard. 

To start things off, we'll choose an arbitrary viewport height of 2.0, and scale the viewport width to give us the desired aspect ratio. 

# 5. Adding a Sphere
Let's add a single object to our ray tracer. People often use spheres in ray tracers becuase calculating whether a ray hits a sphere is relatively simple. 

###  5.1 Ray-Sphere intersection 
equation of a sphere is 
x^2 + y^2 + z^2 = r^2
If a given point  is inside the sphere, then x^2 + y^2 + z^2 < r^2
If a given point  is outside the sphere, then x^2 + y^2 + z^2 > r^2

Using the dot product we can rewrite the equation of the sphere in vector form as (C - P) * ( C - P ) = r^2

We can read this as "any point P that satisfies this equation is on the sphere" We want to know if our ray P(t) = Q td ever hits the sphere anywhere. If it does hit the sphere, there is some t for which P(t) satisfies the sphere equation. So we are looking for any t where this is true: 

(C - P(t)) * (C - P(t)) = r^2


0 roots, misses sphere
1 root, on surface of sphere
2 roots, goes in and out of sphere

### 5.2 Creating our first RayTraced Image
This lacks all sorts of things - like shading, reflection rays, and more than one object - but we are closer to halfway done than we are to our start! One thing to be aware of is that we are testing to see if a ray intersects with the sphere by solving the quadratic equation and seeing if a solution exists but solutions with negative values of t work just fine. 


# 6. Surface Normals and Multiple Objects

### 6.1 Shading with Surface Normals
First, let's get ourselves a surface normal so we can shade. This is a vector that is perpendicular to the surface at the point of intersection. 

We have a key design decision to make for normal vectorsin our code: whether normal vectors will have an arbitrary length or will be normalized to unit length

It is tempting to skip the expensive the expensive square root operation involved in normalizing the vector, in case it's not needed. In practice, however, there are three important observations. First if a unit length normal vector is ever required, then you might as well do it up front once, instead of over and over agiain "just in case" for every location where unit lenght is requred. Second, we do require unit length normal vectors in several places, third if you require normal vectors to be unit length then you can often efficiently generate that vector with an understanding of the specific geometry class, in its constructor, or in the hit() function. 

### 6.2 Simplifying the Ray-Sphere Intersection Code

Lets revisit the ray-sphere function.

### 6.3 An Abstraction for Hittable Objects
Now, how about more than one sphere? While it is tempting to have an array of spheres, a very clean solution is to make an abstract class for anything a ray might hit, and make both a sphere and a list of psheres just something that can be hit. What theat class should be calledis something of a quandary calling it an object would be good if not for the object orieted programming. Surfae is often useed with the weakneass being maybe we want volumes (fog, cloujds) hittable emphasizes that member function that unites them. I dont love any of these but well go with hittable

This hittable abstract class will have a hit function that takes in a ray. 


### 6.4 Front Facees Versus Back Faces

We can have the normal always point against the ray. If the ray is outised the sphere the normal will point outward, if it is inside the sphere the normal will point inward.

### 6.6 Some new C++ features
Hittbale uses vector shared_ptr and makeshared

shared_ptr<type> is a pointer to some allocated type, with reference counting semantics. Every time you assign its value to another shared pointer the reference count is incremented. 

since the type can be automattically deduced by the return type of make_shared<type>(...), the above lines can be more simply expressed using C++'s auto type specifier. 

### 6.7 Common Constants and Utility Functions
We need some math constants that we conventionally define in their own header file. 

### 6.8 An Interval Class
Before we continue, well implement an interval class to manage real valued intervals with a min and max. Well end up using this class quite often.

# 7 Moving Camera Code into its own Class
We will make the camera class, which will 
1. Construct and dipsatch rays into the worlds
2. Use the results of these rays to contruct the rendered image. 