#include "mandelbrot.hpp"

const int width = 800;
const int height = 600;

int main()
{
    Screen scr {};
    ScreenInit (&scr, width, height);

    sf::RenderWindow window(sf::VideoMode(scr.width, scr.height), "SFML window");
    sf::Clock clock;
    sf::Time time;

    sf::Font font;
    font.loadFromFile ("Ubuntu-Bold.ttf");
    int i = 0;

    while (window.isOpen()) {
        if (i == 10) {
            clock.restart().asSeconds();
            i = 0;
        }

        MandelbrotComputing (&scr);
        time = clock.getElapsedTime ();
        sf::Text txt (std::to_string (i / time.asSeconds()), font);
        i++;

        sf::Image im;
        im.create (scr.width, scr.height, (u_int8_t *)scr.color);

        sf::Texture texture;
        texture.create (scr.width, scr.height);
        texture.update (im);

        sf::Sprite spr;
        spr.setTexture (texture);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear ();
        texture.update (im);
        window.draw (spr);
        window.draw (txt);
        window.display ();
    }

    DestrScreen (&scr);

    return 0;
}