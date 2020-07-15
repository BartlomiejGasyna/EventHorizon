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
private:
    int object_ID;
public:
    int HP;
    sf::Sprite Sprite;
    int velocity_x_;
    int velocity_y_;
    int asteroid_ID_;
    Abstract();
    virtual ~Abstract();
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
    virtual void set_asteroid_ID(int asteroid_ID);
    virtual int get_object_ID();
};



#endif // ABSTRACT_H
