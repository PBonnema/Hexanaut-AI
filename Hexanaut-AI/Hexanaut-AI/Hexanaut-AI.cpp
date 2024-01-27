#include <SFML/Graphics.hpp>

import Hexanaut;

int main()
{
    HexanautGame game{ 2, 10, 5 };
    while (!game.step())
        // TODO If human players participate, do a delay each step. Throttle to 60 fps. Can't decouple drawing rate from update rate because that
            // Would require making the time step smaller or bigger, introducing more or less decision moments for the players,
            // Meaning the outcome of the game isn't the same
            // Also do a render call here based on the state of the game.
            // When, where and how to capture player input?
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