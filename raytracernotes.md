# Ray tracing
Each intersecton may spawn secondary rays:
* Rays form a ray tree
* Nodes -> Intersection points
* Edges -> Reflected/transmitted ray

Raus are recursively spawned until
* Ray does not intersect any object
* Tree reaches a maximum depth
* Light reaches some minimum value

Shadow rays are sent from every intersection point (to determin if point is a shadow), but they don not recursively spawn secondary rays

Ray Tree is evaluated from bottom up:
* Depth-first traversal
* Each node's color is calculated as a function  of its childerens colors


# Basic Ray Tracing Algorithm

Generate one ray for each pixel

For each ray:
* Determine the nearest object intersected by the ray
* Compute intensity information for the intersection point using the illumination model
* Calculate and trace reflection ray (if surface is reflective)
* Calculate and trace transmmission ray (if surface is transparent)
* Calculate and trace shadow ray
* Combine results of the intensity computation, reflection ray intensity, transmission ray information
* If the ray misses all objects, set the pixel color to the background color

Tracing Rays
Basic (non-recursive) ray tracing algorithm:
1. Send a ray from the eye through the screen
2. Determine which object that ray first intersects
3. Compute pixel color

Most (approx. 75%) of time in step 2:
* Simple method:
    * compare every ray against every object and remember the closest object hit by each ray
    * Very time consuming, several optimizations possible.

# Ray Representation
A ray can be represented explicitly (in parametric form) as an origin (point) and a direction (vector)

* origin: ro = [x, y, z]
* direction: do = [x, y, z]
* The ray consists of all points:
r(t) = ro +rdt

## Viewing Ray
* The primary ray (or viewing ray) for a point s on the view plane (i.e., screen) is computed as:
* Origin: ro = eye
* Direction: rd = s - eye

Which coordinate space?
* Want to define rays in terms of world-space coods (x, y, z)
* Eye is already specified in terms of (x, y, z) position
* Screen point s is easiest t odefine in terms of where it is on the window in viewing-space coordinates (u, v, w)

Given: 
* Our scene in world coordinates
* A camera (eye) position in world-coordinates (x, y, z)
* A pixel (i, j) in the viewport

We need to 
* Compute the point on the view plane window that corresponds to the (i, j) point in the viewport
* Transform that point into world coordinates

Computing Window Point
* Step 1: Reverse the Window-to-Viewport transformation
    Window-viewport:
        i = (u-u_min) * ((imax - imin)/ (umax - umin)) + i min
        j = (v-v_min) * ((jmax - jmin)/ (vmax - vmin)) + i min
    Inverse tranform (viewport-window)
        u = (i - imin) * ((umax - umin)/(imax - imin)) + umin
        v = (j - jmin) * ((vmax - vmin)/(jmax - jmin)) + vmin

        w = 0

Camera to World tranform
* Given the screen point in terms of camera-space coordinates (u, v, w) transform to world-space (x, y, z):
    * The camera transform takes a point from world space to camera space:

    matmul([
        [ux uy uz 0][1  0  0  -LookAtx]
        [vx vy yz 0][0  1  0  -LookAty]
        [wx wy wz 0][0  0  1  -LookAtz]
        [ 0  0  0 1][0  0  0       1  ]
    ]                                )    


* We want to reverse this:

sworld = Mv^-1[us vs ws 1] = T^-1M_cob^-1[us vs ws 1] = 

    [
        [ux vx wx LookAtx][us]
        [uy vy wy LookAty][vs]
        [uz vz wz LookAtz][ws]
        [0  0   0    1   ][ 1]
    ]

    or 
    S_World = LookAt +usu + vsv + wsw

## Ray Tracing Output
* Probably the simplet approach is to output to a ppm file
* Format:
    * Magic Number
    * number of columns     # of rows
    * Maximum color value
    * RGB RGB RGB

* Magic Number: P3 for ASCII RGB, P6 for binary 
* Uses any whitespace as delimeters

Steps in the Basic Ray tracer
1. Set Camera on the +z axis looking at the origin
2. Determine the size of the image you will generate
3. Determine the window size in (x, y, z)
4. For each pixel
    1. Determine the center of the pixel in (x, y, z) space
    2. Determine the ray direction
    3. Perform intersection tests with each object in the scene, keeping track of the closest object hit
    4. Compute the color of the object at that point
    5. Output the pixel color to the output file

What is the size of a pixel

X direction:
* window size of 4, 8 pixels within that window, pixelx = 0.5
Y direction
* window size of 2, 4 pixels with that window, pixely = .5

In general
* a window size of width containing n pixels gives a pixel size of width/n

E.g. What is the pixel size for a 1280 x 1024 pixel screen, with a world space window that goes between (-160, 160) in x and (-64, 64) in y?

answer: pixelx = 320/1280 = 0.25
        pixely = 128/1024 = 0.125

What point do I send the ray through?


The first pixel center
(-2, 1, 0)              (2, 1, 0)
  .  

(-2, -1, 0)             (2, -1, 0)

n = 8
m = 4
width = 4
height = 2
pixelx = .5
pixely = .5

x' = -width/2 + pixelx/2 = -2 + 0.25 = -1.75
y' = height/2 - pixely/2 = 1 - 0.25 = 0.75



The second pixel center
(-2, 1, 0)              (2, 1, 0)
      .   

(-2, -1, 0)             (2, -1, 0)

n = 8
m = 4
width = 4
height = 2
pixelx = .5
pixely = .5

x' = -width/2 + pixelx/2  + pixelx = -2 + 0.25 +.5 = -1.25
y' = height/2 - pixely/2  = 1 - 0.25 = 0.75



The third pixel center
(-2, 1, 0)              (2, 1, 0)
         .    

(-2, -1, 0)             (2, -1, 0)

n = 8
m = 4
width = 4
height = 2
pixelx = .5
pixely = .5

x' = -width/2 + pixelx/2  + 2*pixelx = -2 + 0.25 + 1 = -0.75
y' = height/2 - pixely/2  = 1 - 0.25 = 0.75



In General
(-2, 1, 0)              (2, 1, 0)
      .   

(-2, -1, 0)             (2, -1, 0)

n = # pixels in x
m = # pixels in y
width = window size in x
height = window size in y
pixelx = size of a pixel in x
pixely = size of a pixel in y

for pixel (i, j)
    - i goint between 0 and n - 1
    - j going between 0 and m - 1
    - n x m pixels
    - (width, height) sized grid centered about the origin.

or 

x' = -width/2 + pixelx/2 + i*pixelx
y' = height/2 - pixely/2 - j*pixely


## Computing the ray
Ray origin Ro = (0,0,d)
ray direction Rd = (x', y', 0) - (0, 0, d) = (x', y', -d) normalized
R(t) = Ro + Rdt = (0, 0, d) + (x', x', y' -d)norm * t

## The Scene
Maintain a list of all objects in the scene. 
Light sources:
* ambient light
* point lights(s) 
* direcional light

## Object List
Maintian Geometry 
* Polygon: vertices
* Sphere: center and radius

Store Material Properties for each object
* Od - the color of the object
* Od - the color of the object
* kd - diffuse coefficient
* ks - specular coefficient
* ka - ambient coefficient
* kgls - glossiness coefficient


Illumniation equation
Itot = kaIaOd + kdIpOd(N . L) + ksIpOs(v * r)kgls

# Ray Object Intersections
* Implicit
    * f(x, y) = 0
    * plug in an (x, y) point
        - if f = 0, the point is on the surface
        - if f < 0, the point is inside the object
        - if f > 0, the point is outside the object
    * easy to determine if a specific 
    * difficuolt 
* parametric
    * (x, y) = f(t) - for a 2D curve
    * (x, y, z) = f(t) - for a 3D surface
    * easy to get all points on the curve or surface
    * difficult to determine if a specific point is on the curve or surface

    Ray-Object Intersections
    * Sphere (with center at c and radius R): fsphere(p) = ||p-c||^2 -R^2 = 0
    * Plane (with normal n and distance to origin d) fplane(p) = p * n + D = 0

### To determine where a ray intersect an object
* Find intersection point p of the ray and the object
* The ray is represented explictyly in parametric form:
    r(t) = ro + rdt
* Plug the ray equation into the surface equation an solve for t:
    f(r(t)) = 0
* Substitute t back into ray equation to find intersection point p: p = r(t) = ro + rdt

### Ray-Sphere 
To find the intersection points of a ray with a sphere:
* Sphere is represented as:
    - center (point): Sc = (xc, yc, zc)
    - and radius (float) : r
* The surface of the sphere is the set of all points (x, y, x) such that 
    (x-xc)^2 + (y - yc)^2 + (z - zc)^2 = r^2
* In this form it is difficult to directly generate surface points
* However, given a point, it is easy to see if the point lies on the surface
* To solve the ray surface intersection, substitue the ray equation into the sphere equation

* First, split the ray into its component equations
    * x = xo + xdt
    * y = yo + ydt
    * z = zo + zdt

* Next substitute the ray equation into the sphree equation 
    (x-xc)^2 + (y - yc)^2 + (z - zc)^2 = r^2
* giving
    (xo + xdt - xc)^2 + (yo + ydt - yc)^2 + (zo +zdt -zc)^2 = r^2
    ==
    (xd^2 + yd^2 +zd^2)t^2 +
    2(xdxo - xdxc + ydyo - ydyc + zdzo - zdzc)t +
    (xo^2 -2xoxc + xc^2 + yo^2 - 2yoyc + yc^2 + zo^2 - 2zozc + zc^2)

    = r^2

Let
* A = xd^2 + yd^2 + zd^2 = 1
* B = 2(xdxo - xdxc + ydyo - ydyc + zdzo - zdzc)
* C = xo^2 - 2xoxc + xc^2+ yo^2 -yoyc + yc^2 + zo^2-2zozc + zc^2 -r^2

* Then At^2 + Bt + C = 0 
* then solve using quadratic equation

t = (-B +- sqrt(B^2 - 4C))/2

### 3 possibilities
* Case 1: Discriminant = 0
    - One real root, to = t1 = B/2
* Case 2: Discrimininant < 0
    - Zero real roots
* Case 3: Discriminant > 0
    - Two real roots
    - Subcase a: t0 < 0, t1 > 0
    t1 is the correct answer
    - Subcase b: t0 > 0, t1 > 0
    t0 is the correct answer

* if the discriminant is negative, the ray misses the sphere
* the smaller positive root is the closer intersection point
* We can save some computation time by computing the smaller root first, then only computing the second root if nessisary

# Ray-Sphere Intersections: Algorithm
Algorithm for ray-sphere intersections
1. Calculate B and C of the quadratic
2. Calculate the discriminant: D = B^2 - 4C
3. If D < 0 return false
4. Calculate smaller intersection parameter to: to = (-B -sqrt(D))/2
5. if to <= 0 then calculate larger t-value t1, t1 = (-B -sqrt(D))/2
6.  If t1 <= 0 return false (intersection point behind ray)
7.  else set t = t1
8. else set t = to
9. Return intersection point: p = r(t) = ro + rdt


Ray-Sphere intersections: Normal
The normal n at an intersection point p on a sphere is 
n = (p - Sc)/r = ((xi - xc)/r (yi - yc)/r (zi - zc)/r)

* Computations time;
    * 17 adds/subtracts
    * 17 multiplies
    * 1 square root

* for each ray/sphere test
* Can we reduce the number of intersections calculations

# Ray-Plane Intersections
To find the intersection points of a ray with an infinite plane:
* Ray equations
    * Origin ro = (xo, yo, zo)
    * Direction: rd = (xd, yd, zd)
* Plane equation:*
    * ax + by +cz + d = 0
    * a^2 + b^2 +c^2  = 1
    * pn = (a, b, c)
* Substitute the ray equation in the plane equation and solve for t

* t = -(axo + byo + czo + d)/(axd +byd + czd)
* In vector form we have 
    * t = -(pn * ro + d)/(pn * rd)

* if pn * rd = 0 the ray is parallel to the plane and does not intersect.
* if pn * rd > 0 the normal of the plane is pointing away from the ray, and thus the plane is culled
* if t < 0 then intersection point is behind the ray, so no real intersection occurs
* Otherwise, compute intersection point: p = ro + rdt

## Ray Plane intersection basic Algorith

compute vd = pn * rd
if vd >= 0 and 1 sided plane then return
if vd = 0 then return (ray parallel to plane)
compute vo = -(pn * ro + d)
compute t = vo / vd
if t < 0 return 
if vd > 0 reverse the plane's normal
return r = (xo + xdt, yo + ydt, zo +) zdt

# Ray / Polygon Intersection
* What about arbitrary polygons
* Assume planar plygons
* First perform the ray / plane intersection with the plane in which the polygon
* How do we quickly tell wheter the point lies within the polygon?
* Idea: Shoot a ray from the intersection point in an arbitrary direction
    * if the ray crosses an even number of polygon edges, the point is outside the polygon
    * If the ray crosses an odd number of polygon edges, the point is inside the polygon
* Polygon
    * a set of N points Gn = (xn, yn, zn) n = 0, 1, ... N-1

# Ray / Polygon Intersecion Algorithm

Step 1
* Project the polygon onto a 2D plane
    - one of the coordinate planes
    - simply discard one of the coordinates 
    - this will project the polygon onto the plane defined by the other two coordinates
    - topology preserving but not area preserving
    - throw away the coordinate whos magnitude in the plane normal is greatest
    - e.g. if Pn = (3, -1, -5) we would through away all the z coordinantes

Step 2
* Translate the polygon so that the intersection point is at the origin
    - apply this translation to all points in the polygon

Step 3:
* Send a ray down one of the coordinate axes and count the number of intersections of that ray with polygon
    - This is done in practice by looking at each polygon edge, one at a time, to see if it crosses the coordinate axis. 

* How do we handle these cases?
    * In essence, shift the vertex or edge up by E so that it will lie in the plane just above the axis
    * This is done by checking for a y value > 0
* What about if the intersection point is exactly a vertex
    * Perform a similar E shift
* What if the intersection point lies exacty on an edge
    * Specify it as either in or out - as long as we do the specification consistently it will work okay
    * If the edge is shared by two polygons, the point will be "in" one polygon and "out" of the other. 

* The Actual Algorithm - Part 1
    1. Determine the dominant coordinate as the largest magnitude component of Pn
    2. For each vertex (xn, yn, zn), n = 0, 1, ..., N-1 of the polygon, project the vertex onto the dominant coordinate axis, giving (un, vn) vertices
    3. Project the intersection point (xint, yint, zint) onto the same coordinate pllane as the vertices
    4. Translate all polygon vertices by (-uint, -vint) giving (un', vn') vertices
    5. Set numCrossings = 0
    6. If vo < 0, set signHolder = -1, otherwise set signHolder = 1
    7. For i = 0 to N-1 (note - when i = N-1, i+1 should be 0)
        a. if vi+1 < 0 set nextSignHolder = -1 else set nextSignHolder = 1
        b. if (signHolder <> nextSignHolder)
            i. if (ui' > 0 and ui+1' > 0) this edge crosses +u' so increment numCrossings
            ii. else if (ui' > 0 or ui+1' > 0) the edge might cross +u', so compute the intersection with the u' axis
                ucross = ui' -vi' * (ui+1' -ui')/(vi+1' -vi')
                if ucross > 0 the edge crosses +u so increment numCrossings
        c. set signHolder = nextSignHolder
    8. If numCrossings is odd, the point is inside the polygon.



# Curve and Surface Types
* f(x, y) = 0
* plug in an (x, y) point
    * if f = 0, the point is on the surface
    * if f < 0, the point is inside the object
    * if f > 0, the point is outside the object
* easy to determine if a specific point is on the sufface
* difficult to find all suface points

## Many objects can be represented as implicit Surfaces
* Sphere
* plane (with normal n and distance to origin d): fplane(p) = p*n + D = 0

* to determine where a ray intersects an object:
    * Need to find the intersection point p of the ray and the object
    * The ray is represented explicityly in parametric form:
        r(t) = r0 +rdt
    * Plug the ray equation into the surface equation and solve for t:
        f(r(t)) = 0
    * Substitute t back into ray equation to find intersection point p:
        p = r(t) = ro +rdt

Remember a ray can be represented as a origin and a direction  (point and vector)
The ray consists of all points
r(t) = ro + rdt

# What about arbitrary polygons?
* assume planar polygons
* first preform the ray/plane intersection with the plane in which the pllygon lies
* Next, determine whether the intersection point lies within the polygon
* How do we quickly tell whetehrh the point lies within the polygon?
## Idea
* Shoot a ray form the intersection point in an arbitray direction
    * if the ray crosses an even number of polygon edges, the point is outside the polygon
    * if the ray crosses an odd number of polygon edges the point is indide the polygon

### Polygon:
polygon: a plane figure with at least three straight sides and angles, and typically five or more
* Polygon: 
    * a set of N points Gn = (xn, yn, zn), n = 0, 1, ... N -1
* Plane:
    * Ax + By + Cz + D = 9, with normal Pn = (A, B, C)


Step 1:
* Project the polygon onto a 2D plane
    * one of the coordinate planes
    * simply discard one of the coordinates
    This will project the polygon onto the plane defined by the other two coordinates
    * Topology preserving but not area preserving
    * throw away the coordinate whos maginitude in the plane is normal is greatest
    *example  if pn = (3, -1, -5) throw away z coordinates

Step 2:
*   Translate the polygon so that the intersection point is at the origin
    - apply this translation to all points in the polygon

Step 3:
* Send a ray down one of the coordinate axes and count the number of intersections of that ray with the polygon
    - This is done in practice by looking at each polygon edge one at a time to see if it crosses the coordinate axis

The Actual Algorithm - Part 1
1. Determine the dominate coordinate as teh largest magnitude component of Pn
2. For each vertex (xn, yn, zn), n = 0, 1, ..., N - 1 of the polygon, project the vertex onto the dominant coordinate axis, giveing (un, and vn) vertices
3. project the intersection point (xint, yint, zint) onto the same coordinate plane as the vertices. 
4. Translate all polygon vertices by (-uint, -vint), giving(un', vn') vertices
5. Set numCrossings = 0
6. If v0' < 0, set signHolder = -1, otherwise set signHolder = 1
7. For i = 0 to N-1 (note -when i = N-1, i+1 should be 0)
    a. if vi+1' < 0, set nextSignHolder = -1 else set nextSignHolder = 1
    b. if (signHolder <> nextSignHolder)
        i. if(ui' > 0 and ui+1' > 0) this edge crosses+u' so invrement numCrossings
        ii. else if (ui' > 0 or ui+1' > 0) the edge might cross +u', so compute the intersection with the u' axis
            ucross = ui' -vi' * (ui+1' -ui)/(vi+1' -vi')
            if ucross > 0 the edge crosses +u so increment numcrossings
    c. set signHolder = nextSignHolder
8. If numCrossings is odd, the pint is inside the polygon