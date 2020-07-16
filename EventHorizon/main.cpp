#include "EventHorizon.h"
#include "abstract.h"
#include "asteroid1.h"
#include "spaceship_new.hpp"
#include "laser.h"
#include "background.h"
#include "bonus.h"
#include "IP_proxy.hpp"

//class Controller
//{
//    sf::RenderWindow window;
//    Spaceship_new player_;
//    std::unique_ptr<Abstract> game_engine_;

//public:
//    Controller(int width = 800, int height = 600)
//            : window(sf::VideoMode(width, height), "Event Horizon Client"), player_(texture_spaceship, window),
//              game_engine_()
//    {

//    }

//};


SingleFrame last_response;

sf::Packet& operator << (sf::Packet& packet, const SingleFrame &frame)
{
    return packet << frame.rotation << frame.is_laser << frame.points <<frame.client_ID;
}

sf::Packet operator >> (sf::Packet packet, SingleFrame frame)
{
    return packet >> frame.rotation >> frame.is_laser >> frame.points >>frame.client_ID;
}

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Client - Event Horizon");
    
    //loading textures, creating objects
    //char data[100];
    std::string data[100];

    //TUTAJ SERWER TYMCZASOWO
    sf::TcpSocket socket;
    sf::IpAddress ip =sf::IpAddress::getLocalAddress();
    int port = 2000;
    std::size_t received;
    
    sf::Socket::Status status = socket.connect("127.0.0.1", 2000); if(status == sf::Socket::Done)
    {
        std::cout<<"nawiazano polaczenie";
    }
    else
        std::cout<<"cos sie spierdolilo";
    
    
    //SPACESHIP
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    sf::Texture texture_spaceship;
    if(!texture_spaceship.loadFromFile("Spaceship2.png")) { std::cout<<"error"; }
    Spaceship_new space(texture_spaceship, window);
    
    sf::Texture texture_second_spaceship;
    if(!texture_second_spaceship.loadFromFile("Spaceship1.png")) { std::cout<<"error"; }
    Spaceship_new opponent(texture_second_spaceship, window);
//    std::cout<<space.getOrigin().x<<"  "<<space.getOrigin().y<<std::endl;
//    std::cout<<space.getPosition().x<<"  "<<space.getPosition().y<<std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///FONT
    sf::Font font;
    if (!font.loadFromFile("Linebeam.ttf")) {
        std::cout<<"Error while loading font"<<std::endl;
    }
    

    //ASTEROIDS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<Abstract*> OBJECTS;
    sf::Texture texture_asteroid_large;
    sf::Texture texture_asteroid_medium;
    sf::Texture texture_asteroid_small;

    if(!texture_asteroid_small.loadFromFile("small_asteroid.png")) { std::cout<<"error"; }
    if(!texture_asteroid_medium.loadFromFile("medium_asteroid.png")) { std::cout<<"error"; }
    if(!texture_asteroid_large.loadFromFile("large_asteroid.png")) { std::cout<<"error"; }

    for (int i = 0; i < 10; i++)
    {
        OBJECTS.push_back(new Asteroid1(&texture_asteroid_small, 1));
        OBJECTS[i]->to_center(window.getSize());
        OBJECTS[i]->Sprite.setScale(0.15, 0.15);
        OBJECTS[i]->set_asteroid_ID(1);
    }

    for (int i = 0; i < 5; i++)
    {
        OBJECTS.push_back(new Asteroid1(&texture_asteroid_medium, 2));
        OBJECTS[i+10]->to_center(window.getSize());
        OBJECTS[i+10]->Sprite.setScale(0.18, 0.18);
        OBJECTS[i+10]->set_asteroid_ID(2);
    }

    for (int i = 0; i < 3; i++)
    {
        OBJECTS.push_back(new Asteroid1(&texture_asteroid_large, 3));
        OBJECTS[i+15]->to_center(window.getSize());
        OBJECTS[i+15]->Sprite.setScale(0.27, 0.27);
        OBJECTS[i+15]->set_asteroid_ID(3);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

    //BONUSES
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<Abstract*> BONUSES;
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
    

    sf::Clock clock;
    
    // run the program as long as the window is open
    while (window.isOpen()) {
        
        SingleFrame request,response;
        
        // check all the window's events that were triggered since the last iteration of the loop
        window.setFramerateLimit(60);
        //EVENTS
        sf::Event event;
        
        static float full_time = 0;
        static float threshold = 0;
        ///Controler
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && threshold >= 250 )
                {
                    space.LASERS.push_back(new Laser(space.getGlobalBounds().left+space.getGlobalBounds().width/2, space.getGlobalBounds().top+space.getGlobalBounds().width/2, space.getRotation()));
                    threshold = 0;
                    space.isLaser = true;
                    
                }
            }

            //CONTROLLER
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            space.controler(event);

        }
        //LOGIC
        sf::Time elapsed = clock.restart();
        full_time+=elapsed.asSeconds();
        threshold+=elapsed.asMilliseconds();


        window.clear(sf::Color::Black);

        background2.render(window); //tworzenie tla
        background2.animuj(elapsed); //animacja tla
//        space.showPoints(font, window);
        window.draw(space.showPoints(font, 0, space.getPoints(), space.getID()));
        window.draw(opponent.showPoints(font, window.getSize().x-400, response.points, response.client_ID ));
        window.draw(space); //tworzenie gracza
        window.draw(opponent);
        space.animuj(elapsed, full_time); //animacja gracza
        opponent.animuj(elapsed, full_time);

        //TA PĘTLA OBSŁUGUJE KOLIZJE POMIEDZY GRACZEM A OBIEKTAMI
        for (unsigned int i = 0; i < OBJECTS.size(); i++)
        {
            OBJECTS[i]->render(window);
            OBJECTS[i]->animuj(elapsed);
            OBJECTS[i]->out_of_screen(window.getSize());
            // ASTEROIDY[i]->getVelocities();
            //std::cout<<"no collision"<<std::endl;

            if(space.getGlobalBounds().intersects(OBJECTS[i]->Sprite.getGlobalBounds()) && OBJECTS[i]->get_object_ID() == 1)
            {
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
            space.LASERS[i]->move(); //animacja lasera

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
                    if (OBJECTS[k]->HP <= 0)
                    {
                        //ASTEROIDY[i]->to_center(window.getSize());
                        // ASTEROIDY.erase(ASTEROIDY.begin()+i);
                        OBJECTS[k]->to_center(window.getSize());
                        std::cout<<"Asteorida pada"<<std::endl;

                    }
                    else OBJECTS[k]->HP--;
                    space.update_points(1);
                    space.LASERS.erase(space.LASERS.begin() + i);
                }
            }
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
                        response_packet >> response.rotation >> response.is_laser >>response.points >>  response.client_ID;
//                        response_packet << response;
        //                if (response.client_ID != space.getID()) {
                        std::cout<<"Odebrane dane: "<<std::endl;
                            std::cout<<"rotacja: "<<response.rotation<<std::endl;
                            std::cout<< "punkty: "<<response.points<<std::endl;
                            std::cout<<"czy laser: " <<response.is_laser<<std::endl;
                            std::cout<<"ID: " <<response.client_ID <<std::endl;
                            std::cout<<std::endl<<std::endl;
                    }
                            opponent.setRotation(response.rotation);

        window.display();
    }
    /////////////////////////////////////////////////////////
    return 0;
}

