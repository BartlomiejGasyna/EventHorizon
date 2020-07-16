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



/*!
 * \brief The Spaceship_new class
 */
class Spaceship_new :public sf::Sprite
{
private:
    bool is_clicked_forward = false;
    bool is_clicked_backward = false;
    int points;
    
    SingleFrame state;
    int ID = 1;
    
    float time;
    sf::Time elapsed;
    sf::Clock clock;
    float threshold;
public:
    std::vector<Laser*> LASERS;
    Spaceship_new(sf::Texture &texture, sf::RenderTarget &target);
    void animuj(const sf::Time &elapsed, float full_time);

    /*!
     * \brief select_forward changes change of controller logical value
     */
    void select_forward();

    /*!
     * \brief select_backward change of controller logical value
     */
    void select_backward();

    /*!
     * \brief unselect_forward change of controller logical value
     */
    void unselect_forward();

    /*!
     * \brief unselect_backward change of controller logical value
     */
    void unselect_backward();

    /*!
     * \brief update_points player scoring update
     * \param x
     */
    void update_points(int x);

    /*!
     * \brief getPoints gets player's points
     * \return
     */
    int getPoints();

    /*!
     * \brief isLaser
     */
    bool isLaser;

    /*!
     * \brief getState
     * \return
     */
    SingleFrame getState();

    /*!
     * \brief getID
     * \return
     */
    int getID();

    /*!
     * \brief controler
     * \param event
     */
    void controler(sf::Event event);
    
    /*!
     *\brief showPoints
     *\return
     *
     **/
    sf::Text showPoints(sf::Font font, int x, int points_, int ID_);

   
    void elapsedTime();
    // updates current full time of the game
    float getTime();
       // returns current full time of the game
    sf::Time getElapsedTime();
    //returns elapsed time as sf::Time
    void updateThreshold(bool reset);
    // if false, resets threshold, if not adds elapsed time
    float getThreshold();
    //return current threshold value
};

#endif /* spaceship_new_hpp */
