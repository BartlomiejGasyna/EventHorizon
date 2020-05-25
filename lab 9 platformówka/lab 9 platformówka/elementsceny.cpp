#include "elementsceny.h"

void ElementSceny::bounce(bool flag)
{
    //    sf::FloatRect guy_bounds = getGlobalBounds();
    //    if(guy_bounds.top <= bounds.top)
    //    {
    //        velocity_y_ = 0;
    //        setPosition(getPosition().x, 0);
    //    }
    //    if(guy_bounds.top + guy_bounds.height >= bounds.bottom)
    //    {
    //        velocity_y_ = 0;
    //        setPosition(getPosition().x, bounds.bottom-guy_bounds.height);
    //    }
    //    if(guy_bounds.left <= bounds.left)
    //    {
    //        velocity_x_ = 0;
    //        setPosition(0, getPosition().y);
    //    }
    //    if(guy_bounds.left + guy_bounds.width >= bounds.right)
    //    {
    //        velocity_x_ = 0;
    //        setPosition(bounds.right-guy_bounds.width, getPosition().y);
    //    }
}

ElementSceny::ElementSceny()
{
}

void ElementSceny::reflection(sf::FloatRect borders)
{
    if(getGlobalBounds().top <= borders.top)
    {
        setPosition(getPosition().x, getPosition().y-1 );
        onGround = true;
        velocity_y_ = 0;
    }

   if(getGlobalBounds().top + getGlobalBounds().height >= borders.top+borders.height)
    {
        setPosition(getPosition().x, getPosition().y+1);
        onGround = true;
        velocity_y_ = 0;
    }


    if(getGlobalBounds().left + getGlobalBounds().width >= borders.left  && sf::Keyboard::isKeyPressed(sf::Keyboard::Right ))
    {
        setPosition(getPosition().x-1, getPosition().y);
    }

    if(getGlobalBounds().left <= borders.left+borders.width && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
    {
        velocity_x_ = -velocity_x_;
        setPosition(getPosition().x+1, getPosition().y);
    }
}

sf::Texture ElementSceny::loadTexture(std::string filename_with_path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename_with_path)) {
        std::cout << "Could not load texture" << std::endl;
    }
    return texture;
}
