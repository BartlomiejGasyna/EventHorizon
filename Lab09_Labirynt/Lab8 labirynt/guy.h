//
//  guy.h
//  Lab9 labirynt
//
//  Created by Bartłomiej Gasyna on 15/05/2020.
//  Copyright © 2020 Bartłomiej Gasyna. All rights reserved.
//
#ifndef GUY_H
#define GUY_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

struct Bounds
{
    int top = 0;
    int bottom = 0;
    int left = 0;
    int right = 0;
};

class object : public sf::Sprite
{
private:
public:
    object(sf::Texture &textures, float x, float y, const sf::IntRect &Bounds)
    {
        setTexture(textures);
        setPosition(x,y);
        setTextureRect(Bounds);
    }
    
};

class guy : public sf::Sprite
{
private:
    Bounds bounds;
public:
    void bounce(sf::FloatRect borders);
    
    guy(sf::Texture &textures);
    void animate(const sf::Time &elapsed);
    void setBounds(int l_bound, int r_bound, int t_bound, int b_bound);
    bool collision(const object body);
};


#endif // GUY_H
