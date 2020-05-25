#include "elementsceny.h"
#include "background.h"
#include "hero.h"
#include "walls.h"

using namespace std;

sf::Texture loadTexture(std::string texture_path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(texture_path)) {
        std::cout << "Could not load texture" << std::endl;
    }
    return texture;
}

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lab_09 Platformowka");

    std::vector<sf::Texture> textures;
    textures.emplace_back(loadTexture("wall.png"));

    std::vector<ElementSceny> obstacle;
    walls wall_1_(textures[0], 125, 100, sf::IntRect(0,0,58,97));
    walls wall_2_(textures[0], 509, 138, sf::IntRect(10,15,100,29));
    walls wall_3_(textures[0], 12, 450, sf::IntRect(45,13,50,250));
    walls wall_4_(textures[0], 450, 12, sf::IntRect(0,0,50,100));
    walls wall_5_(textures[0], 300,300, sf::IntRect(0,0,100,50));
    walls wall_6_(textures[0], window.getSize().x/2, window.getSize().y/2-100, sf::IntRect(0,0,35,200));
    walls wall_7_(textures[0], 100,500, sf::IntRect(0,0,200,50));

    obstacle.emplace_back(wall_1_);
    obstacle.emplace_back(wall_2_);
    obstacle.emplace_back(wall_3_);
    obstacle.emplace_back(wall_4_);
    obstacle.emplace_back(wall_5_);
    obstacle.emplace_back(wall_6_);
    obstacle.emplace_back(wall_7_);


    sf::Texture texture_grass;
    if(!texture_grass.loadFromFile("grass.png")) { return 1; }
    texture_grass.setRepeated(true);
    //    background texture_grass;
    //    texture_grass.loadTexture("grass.png");

    auto size = sf::IntRect(0, 0, window.getSize().x, window.getSize().y);
    background grass(texture_grass, size);

    sf::Texture texture_guy;
    if(!texture_guy.loadFromFile("guy.png")) { return 1; }

    hero guy(texture_guy);
    guy.move(200,200);
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
        
        for (auto &el : obstacle)
        {
            if(guy.getGlobalBounds().intersects(el.getGlobalBounds()))
            {
                guy.onGround = true;
                //std::cout<< "kolizja" <<std::endl;
                //guy.reflection(el.getGlobalBounds());
                if (el.getGlobalBounds().top <= guy.getPosition().y+guy.getGlobalBounds().height) {
                    guy.setPosition(guy.getPosition().x, el.getGlobalBounds().top-guy.getGlobalBounds().height);
                }
                
    
                   
                
                
            }
            
        }
        

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...

        window.draw(grass);
        window.draw(guy);

        for (auto &w : obstacle) {
            window.draw(w);
        }

        // end the current frame
        window.display();
    }
    return 0;
}
