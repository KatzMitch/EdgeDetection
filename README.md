CheckParam.cpp is a program that I wrote to check the efficiency of an
edge detection algorithm. The edge detection algorithm (which I did 
not write) inputs a PGM image and a set of 3 parameters and outputs an image 
file of the edges.

CheckParam.cpp inputs an image and the three parameters and outputs the
edge file as well as a score from 0-100 of how efficienty the edge detection
worked with that set of parameters. The three parameters are the diameter of
the filter, and 2 coefficients for the gaussian function: the center and the
surround.

The best edge detection output images have a high contrast between edges and
the surrounding pixels. An ideal image will have only pixels that are perfectly
either black or white. Therefore, I think the best way to test the image is to 
look at every given pixel and measure:
1) The strength of the color
2) Compare it to the surrounding pixels
The reason I am not measuring the strength of color alone is because, while it
will indicate a potentially correct distribution of color, it does not do
enough to actually check whether you've found edges.

Theoretically, if only edges are marked on an image, there should only be lines
of white pixels. This means that an ideal pixel will be perfectly white with
two neighboring pixels also perfectly white. Every other pixel that touches 
it should be perfectly black. In order to do this measurement, the algorithm will
iterate across the image, checking each pixel and giving it a score. To score
a pixel, I will compare the saturation of the color (so a perfect score will
be either a pixel being either entirely black or white, with a score of 0
being perfect grey), and then if it is a white pixel (so an edge) by seeing
how many neighboring pixels are also edge pixels. Ideally, some of the edge
pixels will touch other edge pixels, but if more than half of the neighboring
pixels are also white then it failed to properly select an edge. That means it
just found a range.

This algorithm will do a good job selecting edge pixels for most
images assuming the image compression is at least somewhat functional, however
it will do a less than ideal job when multiple edges converge
at one location or if the image compression is so broken that the resulting
image is in no way reminiscent of the original. Say if you were to perform an
edge detection on an asterisk,
the center pixel would receive a lower score even if the algorithm was perfect
as it would be marked down for having so many edges touching. Since this should
not happen too much in a typical image I think this corner case will not be
triggered too much, but if you have an image with tons of overlapping edges
it may not receive an ideal score.