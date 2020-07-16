//
//  spaceship_new.cpp
//  EventHorizon
//
//  Created by Bartłomiej Gasyna on 03/07/2020.
//  Copyright © 2020 Bartłomiej Gasyna. All rights reserved.
//

#include "spaceship_new.hpp"
//#include <iostream>

Spaceship_new::Spaceship_new(sf::Texture &texture, sf::RenderTarget &target)
{
    //    alpha = 10;
    //    r = 10;
    //state.ID = 1;
    this->points = 0;
    this->setTexture(texture);
    int size = texture.getSize().y;
    int window_size = target.getSize().y/2;

    setOrigin((texture.getSize().x)/12, size-window_size);
    setPosition(target.getSize().x/2, target.getSize().y/2);
    setTextureRect(sf::IntRect(0,0,70,72));
//    isLaser = false;
    

}

void Spaceship_new::animuj(const sf::Time &elapsed, float full_time)
{
    //std::cout<<time.asSeconds()<<std::endl;
    if(is_clicked_forward == true) {
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
    else if(is_clicked_backward == true) {
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

    else if (is_clicked_forward == false && is_clicked_backward == false)
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

void Spaceship_new::select_backward()
{
    is_clicked_backward = true;
    is_clicked_forward = false;
}

void Spaceship_new::select_forward()
{
    is_clicked_forward = true;
    is_clicked_backward = false;
}

void Spaceship_new::unselect_forward()
{
    is_clicked_forward = false;
}

void Spaceship_new::unselect_backward()
{
    is_clicked_backward = false;
}

void Spaceship_new::update_points(int x)
{
    points = points + x;
    std::cout << "POINTS: " << points << std::endl;
}
int Spaceship_new::getPoints()
{
    return points;
}

SingleFrame Spaceship_new::getState()
{
    
    state.rotation = this->getRotation();
    state.is_laser = this->isLaser;
    state.points = this->points;
//    state.client_id = '1';
    state.client_ID = this->ID;
    std::cout << "ID: " << state.client_ID <<std::endl;
    return state;
}


int Spaceship_new::getID()
{
    return this->ID;
}


void Spaceship_new::controler(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            this->select_forward();
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right) {
            this->select_backward();
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Left) {
            this->unselect_forward();
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Right) {
            this->unselect_backward();
        }
    }
}
