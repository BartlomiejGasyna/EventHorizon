#include "bonus.h"

Bonus::Bonus()
{
    if(!bonus_texture_.loadFromFile("../Resources/bonus.png")) { std::cout<<"error";
    }
    this->Sprite.setTexture(bonus_texture_);
    this->Sprite.setScale(0.2f, 0.2f);
}

Bonus::~Bonus()
{

}

void Bonus::render(sf::RenderTarget &target)
{
    target.draw(this->Sprite);
}

void Bonus::animuj(const sf::Time &elapsed)
{
    this->Sprite.move(velocity_x_*elapsed.asSeconds()*3, velocity_y_*elapsed.asSeconds()*3);
}

void Bonus::to_center(sf::Vector2u size)
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
}

void Bonus::out_of_screen(sf::Vector2u size)
{
    if (this->Sprite.getPosition().x < 0 || this->Sprite.getPosition().x > size.x ||
        this->Sprite.getPosition().y < 0 || this->Sprite.getPosition().y > size.y)
    {
        this->to_center(size);
    }
}

int Bonus::get_object_ID()
{
    return this->object_ID_;
}
