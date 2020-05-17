#include <iostream>
#include "guy.h"

using namespace std;

sf::Texture loadTexture(std::string filename_with_path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename_with_path)) {
        std::cout << "Could not load texture" << std::endl;
    }
    return texture;
}

std::vector<std::unique_ptr<sf::Drawable>> create_shapes(
        const vector<sf::Texture> &textures)
{
    std::vector<std::unique_ptr<sf::Drawable>> shapes;

    {
        auto sprite = make_unique<sf::Sprite>();
        sprite->setTexture(textures[0]);
        sprite->setPosition(50,50);
        sprite->setTextureRect(sf::IntRect(0,0,30,200));
        shapes.emplace_back(move(sprite));
    }

    {
        auto sprite = make_unique<sf::Sprite>();
        sprite->setTexture(textures[0]);
        sprite->setPosition(250,300);
        sprite->setRotation(90.f);
        sprite->setTextureRect(sf::IntRect(0,0,30,200));
        shapes.emplace_back(move(sprite));
    }

    {
        auto sprite = make_unique<sf::Sprite>();
        sprite->setTexture(textures[0]);
        sprite->setPosition(500,500);
        sprite->setTextureRect(sf::IntRect(0,0,120,120));
        shapes.emplace_back(move(sprite));
    }

    {
        auto sprite = make_unique<sf::Sprite>();
        sprite->setTexture(textures[0]);
        sprite->setPosition(300,300);
        sprite->setTextureRect(sf::IntRect(0,0,200,50));
        shapes.emplace_back(move(sprite));
    }

    {
        auto sprite = make_unique<sf::Sprite>();
        sprite->setTexture(textures[0]);
        sprite->setPosition(350,250);
        sprite->setTextureRect(sf::IntRect(0,0,25,200));
        shapes.emplace_back(move(sprite));
    }
    return shapes;
}

int main() {

    vector<sf::Texture> textures;
    textures.emplace_back(loadTexture("wall.png"));

    auto shapes = create_shapes(textures);

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // create some shapes
    sf::Texture texture_grass;
    if(!texture_grass.loadFromFile("grass.png")) { return 1; }
    texture_grass.setRepeated(true);

    sf::Sprite grass;
    grass.setTexture(texture_grass);
    grass.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    sf::Texture texture_guy;
    if(!texture_guy.loadFromFile("guy.png")) { return 1; }

    guy guy(texture_guy);

    guy.setBounds(0, window.getSize().x, 0, window.getSize().y);

    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time elapsed = clock.restart();

        guy.animate(elapsed);

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(grass);
        window.draw(guy);
        for(const auto &s : shapes) {
            window.draw(*s);
        }
        // end the current frame
        window.display();
    }

    return 0;
}
