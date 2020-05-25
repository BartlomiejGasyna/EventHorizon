#include "background.h"

background::background()
{

}

background::background(sf::Texture &texture, sf::IntRect &size)
{
    setTexture(texture);
    setTextureRect(size);
}

//sf::Texture background::loadTexture(std::string filename_with_path)
//{
//    sf::Texture texture;
//    if (!texture.loadFromFile(filename_with_path)) {
//        std::cout << "Could not load texture" << std::endl;
//    }
//    return texture;
//}

void background::animate(const sf::Time &elapsed)
{

}

void background::setBounds(int l_bound, int r_bound, int t_bound, int b_bound)
{

}
