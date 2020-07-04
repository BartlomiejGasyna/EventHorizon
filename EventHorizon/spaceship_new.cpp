//
//  spaceship_new.cpp
//  EventHorizon
//
//  Created by Bartłomiej Gasyna on 03/07/2020.
//  Copyright © 2020 Bartłomiej Gasyna. All rights reserved.
//

#include "spaceship_new.hpp"
#include <iostream>

Spaceship_new::Spaceship_new(float x, float y,  sf::Texture &texture, int velocity_x, int velocity_y, sf::RenderTarget &target)
{
    //    alpha = 10;
    //    r = 10;

    setTexture(texture);
    int size = texture.getSize().y;
    int window_size = target.getSize().y/2;

    setOrigin((texture.getSize().x)/12, size-window_size);
    setPosition(target.getSize().x/2, target.getSize().y/2);
    setTextureRect(sf::IntRect(0,0,70,72));
    //jak zmieniam skale to wywala statek odrobine dalej
    //setScale(1.2, 1.2);
    
    

}

void Spaceship_new::animuj(const sf::Time &elapsed, float full_time)
{
    //std::cout<<time.asSeconds()<<std::endl;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rotate(50*elapsed.asSeconds());
         if (fmod(full_time, 1.0)<0.5)
         {
        setTextureRect(sf::IntRect(280,0,70,72));
         }
        else
        {
            setTextureRect(sf::IntRect(350,0,70,72));
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rotate(-50*elapsed.asSeconds());
        if (fmod(full_time, 1.0)<0.5)
         {
             setTextureRect(sf::IntRect(140,0,70,72));
         }
        else
        {
            setTextureRect(sf::IntRect(210,0,70,72));
        }
        
        
    }
    else
    {
       // if ((int)full_time%2 <1)
        if (fmod(full_time, 1.0)<0.5)
        {
            setTextureRect(sf::IntRect(0,0,70,72));
        }
        else
        {
            setTextureRect(sf::IntRect(70,0,70,72));
        }
        
    }
}
