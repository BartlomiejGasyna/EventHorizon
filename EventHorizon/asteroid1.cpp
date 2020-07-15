#include "asteroid1.h"
#include <iostream>



Asteroid1::Asteroid1(sf::Texture *texture, int life)
{
    this->Sprite.setTexture(*texture);
    this->HP = life;
//    this->setPosition(x, y);
//    this->velocity_y_ = velocity_y;
//    this->velocity_x_ = velocity_x;
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
//        Sprite.setPosition(size.x/2,size.y/2);
//
//        velocity_x_ = (rand() % 20-10)*10;
//        velocity_y_ = (rand() % 20-10)*10;
        this->to_center(size);
        
    }
}

bool Asteroid1::collision(sf::FloatRect object) {
    
    std::cout<<object.width<<std::endl;
//    object.left+=500;
//    object.top+=500;
    sf::FloatRect temp(object.left, object.top, 72,70);
    
    
    std::cout<<"statek - x: "<<object.left<<"  y: "<<object.left+object.width<<std::endl;
    //huj wie czy to dobrze bo wykurwia true caly czas, nie wiem czy to przez sprite przypadkiem, w razie
    if (Sprite.getGlobalBounds().intersects(object))
    //if (Sprite.getGlobalBounds().intersects(object))
    {
        return true;
    };
}
void Asteroid1::to_center(sf::Vector2u size)
{
    this->Sprite.setPosition(size.x/2, size.y/2);
    this->velocity_x_ = (rand() % 20-10)*10;
    this->velocity_y_ = (rand() % 20-10)*10;
    this->HP=2;
}

std::pair<int, int> Asteroid1::getVelocities() {
    return {velocity_x_, velocity_y_};
}

void Asteroid1::create_asteroids(sf::RenderTarget &target)
{

}

int Asteroid1::get_ID()
{
    return this->object_ID_;
}


