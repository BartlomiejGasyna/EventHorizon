#include "abstract.h"
#include "asteroid1.h"
#include "spaceship_new.hpp"
#include "laser.h"
#include "background.h"
#include "bonus.h"


sf::Packet& operator << (sf::Packet& packet, const SingleFrame &frame)
{
    return packet << frame.rotation << frame.is_laser << frame.points <<frame.client_ID << frame.HP;
}

sf::Packet operator >> (sf::Packet packet, SingleFrame frame)
{
    return packet >> frame.rotation >> frame.is_laser >> frame.points >>frame.client_ID >> frame.HP;
}


int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Client - Event Horizon");



    //TUTAJ SERWER TYMCZASOWO
    sf::TcpSocket socket;


    sf::Socket::Status status = socket.connect("127.0.0.1", 2000); if(status == sf::Socket::Done)
    {
        std::cout<<"SERWER CONNECTION";
    }
    else
        std::cout<<"NO SERWER CONNECTION";

    //SPACESHIP
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Texture texture_spaceship;
    if(!texture_spaceship.loadFromFile("../Resources/Spaceship2.png")) { std::cout<<"error"; }
    Spaceship_new space(texture_spaceship, window);

    sf::Texture texture_second_spaceship;
    if(!texture_second_spaceship.loadFromFile("../Resources/Spaceship1.png")) { std::cout<<"error"; }
    Spaceship_new opponent(texture_second_spaceship, window);
//    std::cout<<space.getOrigin().x<<"  "<<space.getOrigin().y<<std::endl;
//    std::cout<<space.getPosition().x<<"  "<<space.getPosition().y<<std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //FONT
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Font font;
    if (!font.loadFromFile("../Resources/Linebeam.ttf")) {
        std::cout<<"Error while loading font"<<std::endl;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //ASTEROIDS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<Abstract*> OBJECTS;
    sf::Texture texture_asteroid_large;
    sf::Texture texture_asteroid_medium;
    sf::Texture texture_asteroid_small;

    if(!texture_asteroid_small.loadFromFile("../Resources/small_asteroid.png")) { std::cout<<"error"; }
    if(!texture_asteroid_medium.loadFromFile("../Resources/medium_asteroid.png")) { std::cout<<"error"; }
    if(!texture_asteroid_large.loadFromFile("../Resources/large_asteroid.png")) { std::cout<<"error"; }

    for (int i = 0; i < 10; i++)
    {
        OBJECTS.push_back(new Asteroid1(&texture_asteroid_small, 0));
        OBJECTS[i]->to_center(window.getSize());
        OBJECTS[i]->Sprite.setScale(0.15, 0.15);
        OBJECTS[i]->set_asteroid_ID(1);
    }

    for (int i = 0; i < 5; i++)
    {
        OBJECTS.push_back(new Asteroid1(&texture_asteroid_medium, 1));
        OBJECTS[i+10]->to_center(window.getSize());
        OBJECTS[i+10]->Sprite.setScale(0.18, 0.18);
        OBJECTS[i+10]->set_asteroid_ID(2);
    }

    for (int i = 0; i < 3; i++)
    {
        OBJECTS.push_back(new Asteroid1(&texture_asteroid_large, 2));
        OBJECTS[i+15]->to_center(window.getSize());
        OBJECTS[i+15]->Sprite.setScale(0.27, 0.27);
        OBJECTS[i+15]->set_asteroid_ID(3);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //BONUSES
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (unsigned int i = 0; i < 3; i++)
    {
        OBJECTS.push_back(new Bonus());
        OBJECTS[i+18]->to_center(window.getSize());
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //BACKGROUND
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Background background2(0.0, 0.0, window);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen()) {

        SingleFrame request,response;

        // check all the window's events that were triggered since the last iteration of the loop

        //EVENTS
        sf::Event event;


        ///Controler
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            //CONTROLLER
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            space.controler(event);
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        }
        //LOGIC
        space.elapsedTime();
        space.updateThreshold(1);


        window.clear(sf::Color::Black);

        background2.render(window); //tworzenie tla
        background2.animuj(space.getElapsedTime()); //animacja tla

        //DISPLAYING POINTS
        window.draw(space.showPoints(font, 0, space.getPoints(), space.getID()));
        window.draw(opponent.showPoints(font, window.getSize().x-425, response.points, response.client_ID ));


        window.draw(space); //tworzenie gracza
        window.draw(opponent);
        space.animuj(space.getElapsedTime(), space.getTime()); //animacja gracza
        opponent.animuj(space.getElapsedTime(), space.getTime());

        //TA PĘTLA OBSŁUGUJE KOLIZJE POMIEDZY GRACZEM A OBIEKTAMI
        for (unsigned int i = 0; i < OBJECTS.size(); i++)
        {
            OBJECTS[i]->render(window);
            OBJECTS[i]->animuj(space.getElapsedTime());
            OBJECTS[i]->out_of_screen(window.getSize());
            // ASTEROIDY[i]->getVelocities();
            //std::cout<<"no collision"<<std::endl;

            if(space.getGlobalBounds().intersects(OBJECTS[i]->Sprite.getGlobalBounds()) && OBJECTS[i]->get_object_ID() == 1)
            {
                space.reduceHP(1);
                OBJECTS[i]->to_center(window.getSize());
                std::cout<<"collision" << std::endl;
            }

            if(space.getGlobalBounds().intersects(OBJECTS[i]->Sprite.getGlobalBounds()) && OBJECTS[i]->get_object_ID() == 2)
            {
                space.update_points(10);
                OBJECTS[i]->to_center(window.getSize());
            }
        }

        //TA PETLA OBSLUGUJE KOLIZJE POMIEDZY LASEREM A OBIEKTAMI
        for (unsigned int i = 0; i < space.LASERS.size(); i++)
        {
            space.LASERS[i]->render(window); //tworzenie lasera
            space.LASERS[i]->animuj(space.getElapsedTime()); //animacja lasera

            //laser poza oknem
            if (space.LASERS[i]->Sprite.getPosition().x > window.getSize().x ||
                    space.LASERS[i]->Sprite.getPosition().y > window.getSize().y)
            {
                delete *(space.LASERS.begin()+i);
                space.LASERS.erase(space.LASERS.begin() + i);
                break;
            }

            //kolizja z obiektami
            for (unsigned int k = 0; k < OBJECTS.size(); k++)
            {
                if (space.LASERS[i]->Sprite.getGlobalBounds().intersects(OBJECTS[k]->Sprite.getGlobalBounds()) && OBJECTS[k]->get_object_ID() == 1)
                {
                    if (OBJECTS[k]->HP_ <= 0)
                    {
                        //ASTEROIDY[i]->to_center(window.getSize());
                        // ASTEROIDY.erase(ASTEROIDY.begin()+i);
                        OBJECTS[k]->to_center(window.getSize());
                        std::cout<<"Asteorida pada"<<std::endl;

                    }
                    else OBJECTS[k]->reduce_HP(1);
                    space.update_points(1);
                    space.LASERS.erase(space.LASERS.begin() + i);
                }
            }
        }

        if(space.getHP() <= 0)
        {
            std::cout<<"You lost!"<<std::endl;
//            window.close();
        }


                request = space.getState();
                sf::TcpSocket socket;
                sf::Socket::Status status = socket.connect("127.0.0.1", 2000);
                sf::Packet request_packet, response_packet;
                    request_packet << request;
                    if(socket.send(request_packet) == sf::Socket::Done)
                    {
                        std::cout<<"Pomyślnie przesłano strukturę"<<std::endl;
                    }
                    else
                    {
                        std::cout<<"Niepowodzenie w transmisji danych"<<std::endl;
                    }
                    sf::sleep(sf::milliseconds(20));
                space.isLaser = false;

        // odbior danych
             if(socket.receive(response_packet) == sf::Socket::Status::Done)
                    {
//                        response_packet >> response;
                        response_packet >> response.rotation >> response.is_laser >> response.points >> response.client_ID >> response.HP;
//                        response_packet >> response.rotation >> response.is_laser >>response.points >>  response.client_ID >> response.HP;
//                        response_packet << response;
        //                if (response.client_ID != space.getID()) {
                        std::cout<<"Odebrane dane: "<<std::endl;
                            std::cout<<"rotacja: "<<response.rotation<<std::endl;
                            std::cout<< "punkty: "<<response.points<<std::endl;
                            std::cout<<"czy laser: " <<response.is_laser<<std::endl;
                            std::cout<<"ID: " <<response.client_ID <<std::endl;
                            std::cout<<"HP: " <<response.HP <<std::endl;
                            std::cout<<std::endl<<std::endl;
                    }
        opponent.setRotation(response.rotation);
        window.display();
    }
    /////////////////////////////////////////////////////////
    return 0;
}
