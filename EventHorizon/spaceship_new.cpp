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
//    setPosition(0,0);
    setScale(1.2, 1.2);
//    setOrigin(-100, 10);
//    setOrigin(31,-435);
    setTextureRect(sf::IntRect(0,0,70,72));
    
    

}
