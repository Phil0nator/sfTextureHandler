#include <SFML/Graphics.hpp>
#include "TextureHandler.hpp"
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Sprite test;
    for (size_t i = 0; i < 256; i++)
    {
        test = TextureHandler::loadImage("bmp_24.bmp");
    }
    
    
    
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(test);

        window.display();
    }

    return 0;
}