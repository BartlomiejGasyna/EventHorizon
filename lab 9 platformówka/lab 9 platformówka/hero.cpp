#include "hero.h"

hero::hero()
{

}

hero::hero(sf::Texture &textures)
{
    setTexture(textures);
}

//sf::Texture hero::loadTexture(std::string filename_with_path)
//{
//    sf::Texture texture;
//    if (!texture.loadFromFile(filename_with_path)) {
//        std::cout << "Could not load texture" << std::endl;
//    }
//    return texture;
//}

void hero::animate(const sf::Time &elapsed)
{
    
    
    //lewo
    sf::FloatRect hero_bounds = getGlobalBounds();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(hero_bounds.left > edge.left)
        {
            move(-400*elapsed.asSeconds(), 0);
        }
    }
    
    
    //prawo
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(hero_bounds.left+hero_bounds.width < edge.right)
        {
            move(400*elapsed.asSeconds(), 0);
        }
    }
    
    
    
    
    //skok
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
       onGround)
    {
        
        std::cout<<"nacisnieto spacje \n";
        if(hero_bounds.left+hero_bounds.width < edge.right)
        {
            //onGround = false;

            move(0, -800*elapsed.asSeconds());
        }
    }
//    onGround = false;
//    if(onGround == false)
//    {
        move(0, 400*elapsed.asSeconds());
//    }
   
}




void hero::setBounds(int l_bound, int r_bound, int t_bound, int b_bound)
{
    edge.top = t_bound;
    edge.bottom = b_bound;
    edge.left = l_bound;
    edge.right = r_bound;
}
