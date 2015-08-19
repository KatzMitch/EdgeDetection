/*
 * Mitchell Katz
 * Thursday, March 5, 2015
 * Neurala Coding Challenge
 * CheckParam.cpp
 */

#include <iostream>
#include <string>
#include <cmath>

#include "Image.hpp"
#include "Kernel.hpp"

/*
 * borderFactor returns a percentage adjustment based on how many white pixels
 * border the original pixel and adjusts the pixel's score accordingly. If I
 * had more time, I would have liked to make more research backed guesses for the
 * values to return. As of now, they are semi-arbitrary based on my intuition.
 */

const float EDGE_SCORES[9] = {0.8, 1.0, 1.0, 1.0, 1.0, 0.9, 0.85, 0.8, 0.75};

float
borderFactor(Image edgePic, int i, int j)
{
        int numEdges = -1;
        //the loops will always count the middle pixel, so we
        //start the count at negative one to remove double-counting

        //A lone pixel or too many touching pixels indicates a bad algorithm
        //a few bording pixels indicates an edge
        for (int m = -1; m <= 1; m++) {
                for (int n = -1; n <= 1; n++) {
                        if (edgePic(i + m, j + n) > 0.5)
                                numEdges++;
                }
        }

        return EDGE_SCORES[numEdges];
}


/*
 * analyzePic determines the contrast in the new image. Pure white is a pixel
 * value of 1.0, and pure black is 0.0. Grey pixels indicate a less effective
 * choice of parameters, so the farther away of a value a pixel has from 0.5,
 * the higher of a score it receives. Analyze pic parses through the image and
 * finds the average distance from the middle value. It calls the borderFactor
 * function to adjust the value based on how many surrounding pixels are also
 * white.
 */
float
analyzePic(Image edgePic)
{
        float contrastScore = 0.0;
        float pixScore;
        int height = edgePic.height();
        int width = edgePic.width();
        for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                        pixScore = 2.0 * fabsf(0.5 - edgePic(i, j));
                        if ((edgePic(i, j) > 0.5 )
                                && (i != 0) && (i != edgePic.height() - 1)
                                && (j != 0) && (j != edgePic.width() - 1))
                                pixScore *= borderFactor(edgePic, i, j);
                                //only call borderFactor on white pixels
                                //black pixels can be in groups
                        contrastScore += pixScore;
                }
        }
        return (contrastScore / edgePic.area()) * 100;
}

/*
 * main reads in the command line arguments for the image to use and the
 * parameters, performs the edge detection, and calls the analyzePic function
 * to assign a score, then prints out the score and saves the edge picture.
 */
int
main(int nArgs, char **args)
{
        std::string infile;
        std::string outfile;
        int diameter;
        float centerW, surroundW;
        float score;

        if (nArgs < 5) {
                std::cerr << "Usage: <image.pgm> <diameter> "
                          << "<centerW> <surroundW>\n";
                return 1;
        } else {
                infile = args[1];
                outfile = infile.substr(0, infile.length() - 4) + "_out.pgm";
                diameter = atoi(args[2]);
                centerW = atof(args[3]);
                surroundW = atof(args[4]);
        }

        try {
                Image original(infile);

                Kernel k(diameter, centerW, surroundW);

                Image edgePic = k.convolve(original);
                edgePic.normalize();
                edgePic.save(outfile);

                score = analyzePic(edgePic);

        } catch (ImageException &e) {
                std::cerr << "Exception Thrown: "
                          << e.what()
                          << "\n";
                return 1;
        }

        std::cout << "With those parameters, the algorithm scored: "
                  << score
                  << "/100\n"
                  << "Edge detection image is saved as: "
                  << outfile
                  << "\n";

        return 0;
}