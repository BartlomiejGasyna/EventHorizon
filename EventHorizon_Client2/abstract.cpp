#include "abstract.h"

Abstract::Abstract()
{

}

Abstract::~Abstract()
{

}

void Abstract::setTexture(sf::Texture &texture)
{
    this->Sprite.setTexture(texture);
}

void Abstract::setPosition(const float x, const float y)
{
    this->Sprite.setPosition(x, y);
}

void Abstract::out_of_screen(sf::Vector2u size)
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
bool Abstract::collision(sf::FloatRect object)
{
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
void Abstract::to_center(sf::Vector2u size)
{
    this->Sprite.setPosition(size.x/2, size.y/2);
    this->velocity_x_ = (rand() % 20-10)*10;
    this->velocity_y_ = (rand() % 20-10)*10;
}
std::pair<int, int> Abstract::getVelocities()
{
    return {velocity_x_, velocity_y_};
}

void Abstract::set_asteroid_ID(int asteroid_ID)
{
    this->asteroid_ID_ = asteroid_ID;
}

int Abstract::get_asteroid_ID()
{
    return this->asteroid_ID_;
}

int Abstract::get_object_ID()
{
    return this->object_ID_;
}

void Abstract::reduce_HP(int damage)
{
    this->HP_ = HP_ - damage;
}

