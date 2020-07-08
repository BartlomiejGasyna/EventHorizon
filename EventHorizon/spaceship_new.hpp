//
//  spaceship_new.hpp
//  EventHorizon
//
//  Created by Bartłomiej Gasyna on 03/07/2020.
//  Copyright © 2020 Bartłomiej Gasyna. All rights reserved.
//

#ifndef spaceship_new_hpp
#define spaceship_new_hpp
#include "laser.h"
#include <stdio.h>
#include <math.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Spaceship_new :public sf::Sprite
{
private:
    bool is_clicked_forward = false;
    bool is_clicked_backward = false;
public:
    //std::vector<Laser> LASERS;
    std::vector<Laser*> LASERS;
    Spaceship_new(float x, float y,  sf::Texture &texture, int velocity_x, int velocity_y, sf::RenderTarget &target);
    void animuj(const sf::Time &elapsed, float full_time);
    void select_forward();
    void select_backward();
    void unselect();
};
#endif /* spaceship_new_hpp */
