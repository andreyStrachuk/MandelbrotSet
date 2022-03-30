#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "mandelbrot.h"

static const double X0 = -3.;
static const double Y0 = -2.;

int main()
{
    Screen scr {};
    ScreenInit (&scr, 800, 600);

    u_int32_t *col = (u_int32_t *)calloc (600 * 800, sizeof (u_int32_t));

    MandelbrotComputing (&scr);

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::Image im;
    im.create (800, 600, sf::Color::Black);
    
    for (int y = 0; y < 600; y++) {
        for (int x = 0; x < 800; x++) {
            sf::Color color(0, 0, 0);

            color.r = (scr.pxls + 800 * y + x)->color;
            color.b = 0;
            color.g = (scr.pxls + 800 * y + x)->color / 5;

            // printf ("%d\n", (scr.pxls + 800 * y + x)->color);
            im.setPixel (x, y, color);
        }
    }

    sf::Texture texture;
    texture.create (800, 600);
    texture.update (im);

    sf::Sprite spr;
    spr.setTexture (texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        texture.update(im);
        window.draw(spr);
        window.display();
    }

    return 0;
}