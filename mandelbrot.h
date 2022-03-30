#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define ASSERT_OK(smth, doSmth)         do { if (smth) { doSmth;}} while (0)

enum ERRORS {
    OK,
    NULLPTR
};

enum RESOFCMP {
    EQUAL,
    MORE,
    LESS
};

struct Pixel {
    double x;
    double y;

    u_int32_t color;
};

struct Screen {
    Pixel *pxls;

    int width;
    int height;
};

int ScreenInit (Screen *scr, const int width, const int height);

int MandelbrotComputing (Screen *scr);

void DestrScreen (Screen *scr);

int DoubleComp (const double value_1, const double value_2);

double CalculateMachineEpsilon ();

#endif