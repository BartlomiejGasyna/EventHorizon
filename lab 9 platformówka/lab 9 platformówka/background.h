#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "elementsceny.h"

class background : public ElementSceny
{
public:
    background();
    background(sf::Texture &texture, sf::IntRect &size);
    //virtual sf::Texture loadTexture(std::string filename_with_path);
    void animate(const sf::Time &elapsed);
    void setBounds(int l_bound, int r_bound, int t_bound, int b_bound);
};

#endif // BACKGROUND_H
