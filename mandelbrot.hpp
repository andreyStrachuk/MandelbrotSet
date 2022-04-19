#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <immintrin.h>

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

struct Screen {
    u_int32_t *color;

    double xc;
    double yc;

    double dX;
    double dY;

    int width;
    int height;
};

int ScreenInit (Screen *scr, const int width, const int height);

int MandelbrotComputing (Screen *scr);

void DestrScreen (Screen *scr);

int DoubleComp (const double value_1, const double value_2);

double CalculateMachineEpsilon ();

void SetColor (Screen *scr, __m256i _N, const int iterX, const int iterY);

void onClick (Screen *scr);

#endif