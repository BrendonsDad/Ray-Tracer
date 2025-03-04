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