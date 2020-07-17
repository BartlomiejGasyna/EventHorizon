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

    this->points = 0;
    this->HP_ = 3;
    this->setTexture(texture);
    int size = texture.getSize().y;
    int window_size = target.getSize().y/2;

    setOrigin((texture.getSize().x)/12, size-window_size);
    setPosition(target.getSize().x/2, target.getSize().y/2);
    setTextureRect(sf::IntRect(0,0,70,72));
    this->time = 0;
    this->threshold = 0;
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

int Spaceship_new::getHP()
{
    return this->HP_;
}

void Spaceship_new::reduceHP(int damage)
{
    this->HP_ = this->HP_ - damage;
}

SingleFrame Spaceship_new::getState()
{
    
    state.rotation = this->getRotation();
    state.is_laser = this->isLaser;
    state.points = this->points;
    state.client_ID = this->ID;
    state.HP = this->HP_;
//    std::cout << "ID: " << state.client_ID <<std::endl;
    return state;
}


int Spaceship_new::getID()
{
    return this->ID;
}

void Spaceship_new::controler(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && getThreshold() >= 250 )
        {
            LASERS.push_back(new Laser(getGlobalBounds().left+getGlobalBounds().width/8, getGlobalBounds().top+getGlobalBounds().height/8, getRotation()));
            updateThreshold(0);
            isLaser = true;

        }
    }

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

sf::Text Spaceship_new::showPoints(sf::Font font, int x, int points_, int ID_)
{
//    std::string pl1_points = "Player 1 :" + std::to_string(points);
    sf::Text text("Player " + std::to_string(ID_) +": " + std::to_string(points_), font, 60);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, 0);
    return text;
}
    
float Spaceship_new::getTime()
{
    return time;
}
void Spaceship_new::elapsedTime()
{
    this->elapsed = this->clock.restart();
    time += this -> elapsed.asSeconds();
}
sf::Time Spaceship_new::getElapsedTime()
{
    return this->elapsed;
}
void Spaceship_new::updateThreshold(bool reset)
{
    if (!reset) {
        threshold = 0;
    }
    else
    {
    threshold += this->elapsed.asMilliseconds();
    }
}
float Spaceship_new::getThreshold()
{
    return threshold;
}

