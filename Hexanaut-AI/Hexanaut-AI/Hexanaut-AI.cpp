#include <SFML/Graphics.hpp>

import Hexanaut;
import A;

int main()
{

    HexanautGame game{ 2, 10 };
    Player p;
    while (!game.step())
        ;
        
        
    // sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    //
    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }
    //
    //     window.clear();
    //     window.draw(shape);
    //     window.display();
    // }

    return 0;
}