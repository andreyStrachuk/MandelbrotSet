#include "mandelbrot.hpp"

int main()
{
    Screen scr {};
    ScreenInit (&scr, 800, 600);

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::Clock clock;
    sf::Time time;

    sf::Font font;
    font.loadFromFile ("Ubuntu-Bold.ttf");

    while (window.isOpen()) {
        MandelbrotComputing (&scr);

        sf::Image im;
        im.create (800, 600, (u_int8_t *)scr.color);

        sf::Texture texture;
        texture.create (800, 600);
        texture.update (im);

        sf::Sprite spr;
        spr.setTexture (texture);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        time = clock.getElapsedTime (); 
        sf::Text txt (std::to_string (1 / time.asSeconds()), font);

        clock.restart().asSeconds(); 

        window.clear ();
        texture.update (im);
        window.draw (spr);
        window.draw (txt);
        window.display ();
    }

    return 0;
}