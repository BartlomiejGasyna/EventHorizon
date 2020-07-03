#include "EventHorizon.h"
#include "abstract.h"
#include "spaceship.h"
#include "asteroid1.h"
#include "spaceship_new.hpp"


float velocity_x0 = 0;
float velocity_x1 = 70;
float velocity_x2 = 90;

float velocity_y1 = 70;
float velocity_y2 = 90;
float velocity_y0 = 0;



int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window");
    
    //loading textures, creating objects
    
    sf::Texture texture_spaceship;
    if(!texture_spaceship.loadFromFile("Spaceship2.png")) { std::cout<<"error"; }
    
    //tutaj jest nowej klasy spaceship_new
     Spaceship_new space(0, 0, texture_spaceship, 0,0, window);

    std::cout<<space.getOrigin().x<<"  "<<space.getOrigin().y<<std::endl;
    std::cout<<space.getPosition().x<<"  "<<space.getPosition().y<<std::endl;

    
    sf::Texture texture_asteroid;
    if(!texture_asteroid.loadFromFile("owoc.png")) { std::cout<<"error"; }

    std::vector<Abstract*> ASTEROIDY;

    for (int i = 0; i < 25; i++)
    {
        ASTEROIDY.push_back(new Asteroid1(0, 0, &texture_asteroid, rand() % 200-100, rand() % 200-100));
        ASTEROIDY[i]->setPosition(window.getSize().x/2, window.getSize().y/2);
    }
    
    float spaceship_angular_velocity = 50;
    
    //BACKGROUND
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sf::Texture texture_background;
    if(!texture_background.loadFromFile("background base.png")) { std::cout<<"error";
    }
    sf::Texture texture_background2;
    if(!texture_background2.loadFromFile("background base2.png")) { std::cout<<"error";
    }
    Background background1(texture_background, 0.0, 0.0, window);
    Background background2(texture_background2, 0.0, 0.0, window);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    sf::Clock clock;
    
    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        window.setFramerateLimit(60);
        //EVENTS
        sf::Event event;
        static float full_time = 0;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //LOGIC
        sf::Time elapsed = clock.restart();
        full_time+=elapsed.asSeconds();
        //std::cout << "Elapsed time: " << elapsed.asMicroseconds()<< std::endl;
        background1.rotate(-0.05);
        background2.rotate(0.05);
    
        
        
        std::vector<sf::CircleShape> asteroids;
        for(int i=0; i<5; i++)
        {

            asteroids.push_back(sf::CircleShape(10));
            asteroids.back().setFillColor(sf::Color::White);
            asteroids.back().setPosition((window.getSize().x)/2, (window.getSize().y)/2);
            window.draw(asteroids.back());
        }
        
        //DRAW
        // clear the window with black color
        window.clear(sf::Color::Black);

        for(auto &it : ASTEROIDY)
        {
            it->out_of_screen(window.getSize());
        }
            
        

        window.draw(background1);
        window.draw(background2);
        
        window.draw(space);
        for(auto &it : asteroids)
        {
            window.draw(it);
        }
        
        for (unsigned int i = 0; i < ASTEROIDY.size(); i++)
        {
            ASTEROIDY[i]->render(window);
            ASTEROIDY[i]->animuj(elapsed);
        }

        
        space.animuj(elapsed);
        
        //window.draw(spaceship_sprite);
        
        
        window.display();
    }
    
    return 0;
}
