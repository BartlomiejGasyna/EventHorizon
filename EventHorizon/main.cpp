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
     Spaceship_new space( (window.getSize().x-72)/2,window.getSize().y-100, texture_spaceship, 0,0);
    //origin zmienia pozycje obiektu o minusowe wartosci
    space.setOrigin(-100, -100);
    std::cout<<space.getOrigin().x<<"  "<<space.getOrigin().y<<std::endl;
    
    //tu stworzyłem tymczasowy statek zeby pokombinować ze zmiana origin
    sf::Sprite statek_temp;
    statek_temp.setTextureRect(sf::IntRect(0,0,70,72));
    
//    statek_temp.setOrigin(100, 100);
    statek_temp.setPosition(200, 200);
    statek_temp.setTexture(texture_spaceship);
    
    
    sf::Texture texture_asteroid;
    if(!texture_asteroid.loadFromFile("owoc.png")) { std::cout<<"error"; }

    std::vector<Abstract*> ASTEROIDY;

    for (int i = 0; i < 5; i++)
    {
        ASTEROIDY.push_back(new Asteroid1(0, 0, &texture_asteroid, rand() % 100-200, rand() % 100-200));
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


        

        window.draw(background1);
        window.draw(background2);
        window.draw(statek_temp);
        
        
        for(auto &it : asteroids)
        {
            window.draw(it);
        }
        
        for (unsigned int i = 0; i < ASTEROIDY.size(); i++)
        {
            ASTEROIDY[i]->render(window);
            ASTEROIDY[i]->animuj(elapsed);
        }
        
        window.draw(space);
        
        //window.draw(spaceship_sprite);
        
        
        window.display();
    }
    
    return 0;
}





