#include "asteroid1.h"
#include <iostream>



Asteroid1::Asteroid1(sf::Texture *texture, int life)
{
    this->Sprite.setTexture(*texture);
    this->HP_ = life;
}

Asteroid1::~Asteroid1()
{

}

void Asteroid1::render(sf::RenderTarget &target)
{
    target.draw(this->Sprite);
}

void Asteroid1::animuj(const sf::Time &elapsed)
{
    this->Sprite.move(this->velocity_x_*elapsed.asSeconds()*3, this->velocity_y_*elapsed.asSeconds()*3);
}

void Asteroid1::out_of_screen(sf::Vector2u size)
{
    if (this->Sprite.getPosition().x < 0 || this->Sprite.getPosition().x > size.x ||
            this->Sprite.getPosition().y < 0 || this->Sprite.getPosition().y > size.y)
    {
        this->to_center(size);
    }
}

bool Asteroid1::collision(sf::FloatRect object) {
    
    std::cout<<object.width<<std::endl;
    //    object.left+=500;
    //    object.top+=500;
    sf::FloatRect temp(object.left, object.top, 72,70);
    
    
    std::cout<<"statek - x: "<<object.left<<"  y: "<<object.left+object.width<<std::endl;

    if (Sprite.getGlobalBounds().intersects(object))
    {
        return true;
    }
    return false;
}
void Asteroid1::to_center(sf::Vector2u size)
{
    this->Sprite.setPosition(size.x/2, size.y/2);
    this->velocity_x_ = (rand() % 20-10)*10;
    this->velocity_y_ = (rand() % 20-10)*10;

    if(this->velocity_x_ == 0)
    {
        this->velocity_x_ = (rand() % 20-10)*10;
    }

    if(this->velocity_y_ == 0)
    {
        this->velocity_y_ = (rand() % 20-10)*10;
    }
    if(this->get_asteroid_ID() == 1) this->HP_ = 0;
    if(this->get_asteroid_ID() == 2) this->HP_ = 1;
    if(this->get_asteroid_ID() == 3) this->HP_ = 2;
}

std::pair<int, int> Asteroid1::getVelocities()
{
    return {velocity_x_, velocity_y_};
}

void Asteroid1::set_asteroid_ID(int ID)
{
    this->asteroid_ID_ = ID;
}

int Asteroid1::get_asteroid_ID()
{
    return this->asteroid_ID_;
}

int Asteroid1::get_object_ID()
{
    return this->object_ID_;
}

void Asteroid1::reduce_HP(int damage)
{
    this->HP_ = HP_ - damage;
}


