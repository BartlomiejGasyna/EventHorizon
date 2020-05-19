//
//  main.cpp
//  Lab9 labirynt
//
//  Created by Bartłomiej Gasyna on 15/05/2020.
//  Copyright © 2020 Bartłomiej Gasyna. All rights reserved.
//

#include "guy.h"

using namespace std;

sf::Texture loadTexture(std::string texture_path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(texture_path)) {
        std::cout << "BŁĄD PRZY WCZYTYWANIU TEKSTURY" << std::endl;
    }
    return texture;
}


int main() {
    
    

    vector<sf::Texture> textures;
    textures.emplace_back(loadTexture("wall.png"));

   
    //TWORZENIE SCIAN
    // WALL(TEXTURA, POLOZENIE X, POLOZENIE Y, WYMIARY)
    std::vector<object> walls;
    object wall1(textures[0], 50, 50, sf::IntRect(0,0,30,200));
    object wall2(textures[0], 250, 300, sf::IntRect(0,0,30,200));
    object wall3(textures[0], 500, 500, sf::IntRect(0,0,120,120));
    object wall4(textures[0], 300, 300, sf::IntRect(0,0,200,50));
    object wall5(textures[0], 250,250, sf::IntRect(0,0,30,200));
 
    walls.emplace_back(wall1);
    walls.emplace_back(wall2);
    walls.emplace_back(wall3);
    walls.emplace_back(wall4);
    walls.emplace_back(wall5);
    
    
    // okno
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // obiekty
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

    // główna pętla
    while (window.isOpen()) {
        // SPRAWDZANIE EVENTOW
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time elapsed = clock.restart();

        guy.animate(elapsed);
        
        
        //KOLIZJE
        for (auto &w : walls)
        {
       //if(guy.getGlobalBounds().intersects(w.getGlobalBounds())) /
            if(guy.collision( w)) // SPR. CZY KOLIZJA
        {
            //std::cout<< "kolizja" <<std::endl;
            //kontrola kolizji
            guy.bounce(w.getGlobalBounds()); //METODA WYKONYWANA W TRAKCIE  KOLIZJI
        }
        else
            ;
            //std::cout<< std::endl;
            //kontrola kolizji
        }
        
        
        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(grass);
        window.draw(guy);
        window.draw(wall1);
        
        for (auto &w : walls) {
            window.draw(w);
        }
        
        
        
        

        window.display();
        //guy.bounce(wall2.getGlobalBounds());
//        for (auto &w : walls)
//        {
//            guy.bounce(w.getGlobalBounds());
//        }
        
    
    }
         

//    for(auto &el : walls)
//    {
//        if(guy.getLocalBounds().intersects(el.getLocalBounds()))
//            std::cout<< " kolizja" <<std::endl;
//
//    }
    
    
    return 0;
}
