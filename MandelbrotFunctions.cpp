#include "mandelbrot.hpp"

int X0 = 0.;
int Y0 = 0;

int ScreenInit (Screen *scr, const int width, const int height) {
    void *ptr = calloc (width * height, sizeof (u_int32_t));
    ASSERT_OK (ptr == nullptr, return NULLPTR);
    scr->color = (u_int32_t *)ptr;

    scr->width = width;
    scr->height = height;

    scr->dX = 1. / 200;
    scr->dY = 1. / 200;

    scr->xc = -0.6;
    scr->yc = 0.35;

    return OK;
}

int MandelbrotComputing (Screen *scr) {
    assert (scr);

    int maxN = 256;

    double maxDistance = 100.;

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right))   scr->xc -= (scr->dX * 50.);
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left))    scr->xc += (scr->dX * 50.);
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Up))      scr->yc += (scr->dY * 50.);
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Down))    scr->yc -= (scr->dY * 50.);
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Q)) {
        scr->dY /= 1.5;
        scr->dX /= 1.5; 
    }
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::W)) {
        scr->dY *= 1.5;
        scr->dX *= 1.5; 
    }

    for (int iterY = 0; iterY < scr->height; iterY++) {

        double x0 = -300. * scr->dX + scr->xc * scr->dX * 300.;
        double y0 = ((double)iterY - 400.) * scr->dY + scr->yc * scr->dY * 400;

        for (int iterX = 0; iterX < scr->width; iterX++, x0 = x0 + scr->dX) {

            double x = x0;
            double y = y0;

            int n = 0;
            for ( ; n < maxN; n++) {
                double X_Y = x * y;

                double X_n2 = x * x;
                double Y_n2 = y * y;

                double d = X_n2 + Y_n2;

                if (DoubleComp (d, maxDistance) == MORE)
                    break;

                x = X_n2 - Y_n2 + x0;
                y = X_Y + X_Y + y0;
            }

            *(scr->color + scr->width * iterY + iterX) = SetColor (n);     
        }

    }

    return OK;
}

void DestrScreen (Screen *scr) {
    assert (scr);

    free (scr->color);

    scr->height = 0;
    scr->width = 0;
}


int DoubleComp (const double value_1, const double value_2) {
    double epsilon = CalculateMachineEpsilon ();
    if (fabs (value_2 - value_1) <= epsilon) {
        return EQUAL;
    }
    else if (value_1 > value_2) {
        return MORE;
    } else {
        return LESS;
    }
}

double CalculateMachineEpsilon () {
    double epsilon = 1.0;

    while ((1 + epsilon) > 1) {
        epsilon /= 2;
    }

    return epsilon;
}

u_int32_t SetColor (const int n) {

    u_int32_t col = n * 25;
    col <<= 24;
    col += 255;

    return col;
}