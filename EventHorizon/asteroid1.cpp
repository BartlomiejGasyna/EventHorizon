#include "asteroid1.h"
#include <iostream>

Asteroid1::Asteroid1(float x, float y, sf::Texture *texture, int velocity_x, int velocity_y)
{
    this->setTexture(*texture);
    this->setPosition(x, y);
    this->velocity_y_ = velocity_y;
    this->velocity_x_ = velocity_x;
}

void Asteroid1::render(sf::RenderTarget &target)
{
    target.draw(this->Sprite);
}

void Asteroid1::animuj(const sf::Time &elapsed)
{
    this->move(velocity_x_*elapsed.asSeconds()*3, velocity_y_*elapsed.asSeconds()*3);
}

void Asteroid1::out_of_screen(sf::Vector2u size)
{
    if (Sprite.getPosition().x < 0 || Sprite.getPosition().x > size.x ||
        Sprite.getPosition().y < 0 || Sprite.getPosition().y > size.y)
    {
        Sprite.setPosition(size.x/2,size.y/2);
        
        velocity_x_ = (rand() % 20-10)*10;
        velocity_y_ = (rand() % 20-10)*10;
        
    }
}

bool Asteroid1::collision(sf::FloatRect const object) {
    if (Sprite.getGlobalBounds().intersects(object)) {
        return true;
    };
}


