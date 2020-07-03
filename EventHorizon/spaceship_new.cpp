//
//  spaceship_new.cpp
//  EventHorizon
//
//  Created by Bartłomiej Gasyna on 03/07/2020.
//  Copyright © 2020 Bartłomiej Gasyna. All rights reserved.
//

#include "spaceship_new.hpp"
Spaceship_new::Spaceship_new(float x, float y,  sf::Texture &texture, int velocity_x, int velocity_y)
{
    //    alpha = 10;
    //    r = 10;
    
    //setPosition(x, y);
    setTexture(texture);

int size = texture.getSize().y;
    //setScale(1.2, 1.2);
    setOrigin((texture.getSize().x)/12, size-500);
    setPosition(500, 500);
    //    setOrigin(31,-435);
    setTextureRect(sf::IntRect(0,0,70,72));
    
    

}

void Spaceship_new::animuj(const sf::Time &elapsed)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rotate(50*elapsed.asSeconds());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rotate(-50*elapsed.asSeconds());
    }
}
