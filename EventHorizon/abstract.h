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
    int client_ID;
    
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
    virtual void setTexture(sf::Texture& texture); //ustawianie tekstury
    virtual void setPosition(const float x, const float y); //ustawianie pozycji
    virtual void render(sf::RenderTarget& target) = 0; //renderowanie obiektu
    virtual void animuj(const sf::Time &elapsed) = 0; //animacja obiektu
    virtual void move(const float x, const float y); //poruszanie się obiektu
    virtual void out_of_screen(sf::Vector2u size); //wykrywa wyjście obiektu poza ekran
    virtual bool collision(sf::FloatRect object); //kolizja pomiędzy obiektami
    virtual void to_center(sf::Vector2u size); //nadanie nowej pozycji
    virtual std::pair<int, int>getVelocities();
    virtual void set_asteroid_ID(int asteroid_ID); //nadawanie numeru identyfikacyjnego asteroidy
    virtual int get_asteroid_ID(); //pobieranie numeru identyfikacyjnego asteroidy
    virtual int get_object_ID(); //pobieranie numeru identyfikacyjnego obiektu
};



#endif // ABSTRACT_H
