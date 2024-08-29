converts inserted image to ascii

## what is ascii
+ charecter encoding standard that asigns numeric valeues to letters

## ASCII
# Understanding the concept:

- Each character represents a certain level of brightness or color intensity.
- characters (like '@' or '#') represent darker areas, characters (like '.' or ' ') represent brighter areas.

# Steps for implementation:

- Image input:
    + Learn how to read image files in C using a library like stb_image or libpng.
    + Understand accesing pixel data from the loaded image.

- Grayscale conversion:
    + If the image is color, convert to grayscale. (simplifies as you'll only deal with brightness levels).
    + Research the formula for converting RGB to grayscale (common formula: 0.299R + 0.587G + 0.114B).

- Resizing:
    + ASCII characters are larger than pixels, so resize the image.
    + Learn about image scaling algorithms like nearest neighbor or bilinear interpolation.

- Character mapping:
    + Create a mapping between brightness levels and ASCII characters.
    + Divide the brightness range (0-255) into segments, each represented by a character.

- Output generation:
    + For each pixel in the resized image, determine its brightness and map it to an ASCII character.
    + Print these characters to the console or write them to a file.


Additional considerations:

Handle different image formats and color depths.
Consider aspect ratio differences between characters and pixels.
Experiment with different character sets for various effects.


C-specific guidance:

Familiarize yourself with file I/O in C for reading image files and writing output.
Learn about dynamic memory allocation for handling image data.
Understand 2D arrays or pointer arithmetic for manipulating image pixels.
Practice using external libraries in C for image processing tasks.


Testing and refinement:

Start with small, simple images and gradually increase complexity.
Experiment with different character sets and mappings.
Compare your results with existing ASCII art generators to improve your algorithm.