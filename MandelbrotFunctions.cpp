#include "mandelbrot.hpp"

int ScreenInit (Screen *scr, const int width, const int height) {
    void *ptr = calloc (width * height, sizeof (u_int32_t));
    ASSERT_OK (ptr == nullptr, return NULLPTR);
    scr->color = (u_int32_t *)ptr;

    scr->width = width;
    scr->height = height;

    scr->dX = 1.f / width * 4;
    scr->dY = 1.f / width * 4;

// setting Xc and Yc. these params found empirically_))
    scr->xc = -0.6f;
    scr->yc = 0.35f;

    return OK;
}

int MandelbrotComputing (Screen *scr) {
    assert (scr);

    int maxN = 256;

    __m256d _maxDistance = _mm256_set1_pd (100.f);
    __m256d _multipliers_arr = _mm256_set_pd (3.f, 2.f, 1.f, 0.f);

    onClick (scr);
    
    for (int iterY = 0; iterY < scr->height; iterY++) {

        double x0 = -scr->height / 2 * scr->dX + scr->xc * scr->dX * scr->height / 2;
        double y0 = ((double)iterY - scr->width / 2) * scr->dY + scr->yc * scr->dY * scr->width / 2;

        __m256d _dX = _mm256_set1_pd (scr->dX);
    
        __m256d _y0_arr = _mm256_set1_pd (y0);

        int mask = 0;

        for (int iterX = 0; iterX < scr->width; iterX += 4, x0 += (4. * scr->dX)) {
            
            __m256d _x0_arr = _mm256_add_pd (_mm256_set1_pd (x0), _mm256_mul_pd (_multipliers_arr, _dX));

            __m256d _x_arr = _x0_arr;
            __m256d _y_arr = _y0_arr;

            __m256i _N = _mm256_setzero_si256 ();
            
            for (int n = 0; n < maxN; n++) {
                __m256d _x2_arr = _mm256_mul_pd (_x_arr, _x_arr);
                __m256d _y2_arr = _mm256_mul_pd (_y_arr, _y_arr);
                __m256d _xy_arr = _mm256_mul_pd (_x_arr, _y_arr);

                __m256d _cmp_arr = _mm256_cmp_pd (_mm256_add_pd (_x2_arr, _y2_arr), _maxDistance, _CMP_LT_OQ);
                mask = _mm256_movemask_pd (_cmp_arr);
                if (!mask) {
                    break;
                }

                _N = _mm256_sub_epi64 (_N, _mm256_castpd_si256 (_cmp_arr));

                _x_arr = _mm256_add_pd (_mm256_sub_pd (_x2_arr, _y2_arr), _x0_arr);     // x = X_n2 - Y_n2 + x0;

                _y_arr = _mm256_add_pd (_mm256_add_pd (_xy_arr, _xy_arr), _y0_arr);     // y = X_Y + X_Y + y0;

                SetColor (scr, _N, iterX, iterY);
            }
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

inline void SetColor (Screen *scr, __m256i _N, const int iterX, const int iterY) {

    for (int i = 0; i < 4; i++) {
        u_int32_t col = _N[i] << 24;
        col *= 25;
        col += 255;
        *(scr->color + 800 * iterY + iterX + i) = col;
    }

}

inline void onClick (Screen *scr) {
    
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right))   scr->xc -= (scr->dX * 50.);
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left))    scr->xc += (scr->dX * 50.);
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Up))      scr->yc += (scr->dY * 50.);
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Down))    scr->yc -= (scr->dY * 50.);
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Q)) {
        scr->dY /= 1.5f;

        scr->dX /= 1.5f; 
    }
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::W)) {
        scr->dY *= 1.5f;
        scr->dX *= 1.5f; 
    }
    
}