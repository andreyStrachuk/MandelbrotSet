#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "mandelbrot.h"

int main()
{
    Screen scr {};
    ScreenInit (&scr, 800, 600);

    MandelbrotComputing (&scr);

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::Image im;
    im.create (800, 600, (u_int8_t *)scr.color);

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