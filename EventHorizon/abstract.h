#ifndef ABSTRACT_H
#define ABSTRACT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <math.h>

struct SingleFrame
{
    float rotation;
    bool is_laser;
    int points;
//    char client_id;
    int client_ID;
    // to trzeba bedzie dodac
    //std::vector<std::pair<int, int>>asteroids_speed;
    
};



class Abstract : public sf::Sprite
{
public:
    int HP;
    Abstract();
    virtual ~Abstract();
    sf::Sprite Sprite;
    virtual void setTexture(sf::Texture& texture);
    virtual void setPosition(const float x, const float y);
    virtual void render(sf::RenderTarget& target) = 0;
    virtual void animuj(const sf::Time &elapsed) = 0;
    virtual void move(const float x, const float y);
    virtual void out_of_screen(sf::Vector2u size);
    // Wykrywa wyjście asteroidy poza ekran
    virtual bool collision(sf::FloatRect object);
    // kolizje z graczami
    virtual void to_center(sf::Vector2u size);
    virtual std::pair<int, int>getVelocities();
    
};



#endif // ABSTRACT_H
