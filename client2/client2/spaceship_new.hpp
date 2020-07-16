//
//  spaceship_new.hpp
//  EventHorizon
//
//  Created by Bartłomiej Gasyna on 03/07/2020.
//  Copyright © 2020 Bartłomiej Gasyna. All rights reserved.
//

#ifndef spaceship_new_hpp
#define spaceship_new_hpp
#include "laser.h"
//#include "abstract.h"
//#include "IP_proxy.hpp"
//#include <stdio.h>
//#include <math.h>
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/System.hpp>




class Spaceship_new :public sf::Sprite
{
private:
    bool is_clicked_forward = false;
    bool is_clicked_backward = false;
    int points;
    SingleFrame state;
    int ID = 2;
public:
    std::vector<Laser*> LASERS;
    Spaceship_new(sf::Texture &texture, sf::RenderTarget &target);
    void animuj(const sf::Time &elapsed, float full_time);
    void select_forward(); //zmiana wartości logicznej kontrolera
    void select_backward(); //zmiana wartości logicznej kontrolera
    void unselect_forward(); //zmiana wartości logicznej kontrolera
    void unselect_backward(); //zmiana wartości logicznej kontrolera
    void update_points(int x); //aktualizacja punktacji gracza
    int getPoints(); //pobieranie punktacji gracza
    bool isLaser;
    SingleFrame getState();
    int getID();
    void controler(sf::Event event);
};



#endif /* spaceship_new_hpp */

