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

/*!
 * \brief The Spaceship_new class
 */
class Spaceship_new :public sf::Sprite
{
private:
    bool is_clicked_forward = false;
    bool is_clicked_backward = false;
    int points;
    int HP_;
    
    SingleFrame state;
    int ID = 2;
    
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
     * \param x number of points
     */
    void update_points(int x);

    /*!
     * \brief getPoints gets player's points
     * \return return points
     */
    int getPoints();

    /*!
     * \brief getHP
     * \return number of HP
     */
    int getHP();

    /*!
     * \brief reduceHP
     * \param damage
     */
    void reduceHP(int damage);

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
     * \return number of ID
     */
    int getID();

    /*!
     * \brief controler
     * \param event
     */
    void controler(sf::Event event);
    
    /*!
     * \brief showPoints
     * \param font
     * \param x
     * \param points_
     * \param ID_
     * \return
     */
    sf::Text showPoints(sf::Font font, int x, int points_, int ID_);

    /*!
     * \brief elapsedTime updates current full time of the game
     */
    void elapsedTime();

    /*!
     * \brief getTime
     * \return current full time of the game
     */
    float getTime();

    /*!
     * \brief getElapsedTime
     * \return elapsed time as sf::Time
     */
    sf::Time getElapsedTime();

    /*!
     * \brief updateThreshold if false, resets threshold, if not adds elapsed time
     * \param reset
     */
    void updateThreshold(bool reset);

    /*!
     * \brief getThreshold
     * \return current threshold value
     */
    float getThreshold();
};

#endif /* spaceship_new_hpp */

