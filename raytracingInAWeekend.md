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