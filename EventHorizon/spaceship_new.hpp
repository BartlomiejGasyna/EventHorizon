//
//  spaceship_new.hpp
//  EventHorizon
//
//  Created by Bartłomiej Gasyna on 03/07/2020.
//  Copyright © 2020 Bartłomiej Gasyna. All rights reserved.
//

#ifndef spaceship_new_hpp
#define spaceship_new_hpp

#include <stdio.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Spaceship_new :public sf::Sprite
{
public:
    Spaceship_new(float x, float y,  sf::Texture &texture, int velocity_x, int velocity_y, sf::RenderTarget &target);
    void animuj(const sf::Time &elapsed);

};
#endif /* spaceship_new_hpp */
