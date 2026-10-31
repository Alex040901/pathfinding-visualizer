
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow ventana(
        sf::VideoMode({ 800, 600 }),
        "Pathfinding Visualizer"
    );

    while (ventana.isOpen())
    {
        while (const auto evento = ventana.pollEvent())
        {
            if (evento->is<sf::Event::Closed>())
                ventana.close();
        }

        ventana.clear(sf::Color::White);
        ventana.display();
    }

    return 0;
}
