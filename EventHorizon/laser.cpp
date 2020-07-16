#include "laser.h"

Laser::Laser(int pos_x_, int pos_y_, float rotation)
{
    if(!laser_texture_.loadFromFile("doge.png")) { std::cout<<"error"; }

    this->Sprite.setTexture(laser_texture_);
    this->Sprite.setScale(0.07f, 0.07f);
    this->Sprite.setPosition(pos_x_, pos_y_);
    this->radians_ = (rotation / 180) * M_PI;
}

Laser::~Laser()
{

}

void Laser::render(sf::RenderTarget &target)
{
    target.draw(this->Sprite);
}

void Laser::animuj(const sf::Time &elapsed)
{
    this->Sprite.move(4*sin(this->radians_)*elapsed.asSeconds(),-4*cos(this->radians_)*elapsed.asSeconds());
}
void Laser::move()
{
    this->Sprite.move(4*sin(this->radians_),-4*cos(this->radians_));
}
