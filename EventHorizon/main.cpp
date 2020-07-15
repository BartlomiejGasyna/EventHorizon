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

        //send/receive data
        socket.receive(&data, 100, received);
        //
        for (int i =0; i!=100; i++) {
            //                    while (data[i]) {
            //                        std::cout<<data[i];
            //                    }
            std::cout<<data[i];

        }
        //socket.disconnect();
    }
    else
        std::cout<<"cos sie spierdolilo";
    
    
    //SPACESHIP
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sf::Texture texture_spaceship;
    if(!texture_spaceship.loadFromFile("Spaceship2.png")) { std::cout<<"error"; }
    Spaceship_new space(texture_spaceship, window);

    std::cout<<space.getOrigin().x<<"  "<<space.getOrigin().y<<std::endl;
    std::cout<<space.getPosition().x<<"  "<<space.getPosition().y<<std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
        BONUSES.push_back(new Bonus());
        BONUSES[i]->to_center(window.getSize());
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //BACKGROUND
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Background background2(0.0, 0.0, window);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

    sf::Clock clock;
    
    // run the program as long as the window is open
    while (window.isOpen()) {
        

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
                //                space.isLaser = false;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    space.select_forward();
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    space.select_backward();
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Left) {
                    space.unselect_forward();
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Right) {
                    space.unselect_backward();
                }
            }

        }
        //LOGIC
        sf::Time elapsed = clock.restart();
        full_time+=elapsed.asSeconds();
        threshold+=elapsed.asMilliseconds();


        window.clear(sf::Color::Black);

        background2.render(window);
        background2.animuj(elapsed);

        window.draw(space);
        space.animuj(elapsed, full_time);

        //TA PĘTLA OBSŁUGUJE KOLIZJE
        for (unsigned int i = 0; i < OBJECTS.size(); i++)
        {
            OBJECTS[i]->render(window);
            OBJECTS[i]->animuj(elapsed);
            OBJECTS[i]->out_of_screen(window.getSize());
            // ASTEROIDY[i]->getVelocities();
            //std::cout<<"no collision"<<std::endl;

            if(space.getGlobalBounds().intersects(OBJECTS[i]->Sprite.getGlobalBounds()))
            {
                OBJECTS[i]->to_center(window.getSize());
                std::cout<<"collision" << std::endl;
            }
        }

        for (unsigned int i = 0; i < space.LASERS.size(); i++)
        {
            space.LASERS[i]->render(window);
            //Move
            space.LASERS[i]->move();

            //Out of window bounds
            if (space.LASERS[i]->Sprite.getPosition().x > window.getSize().x ||
                    space.LASERS[i]->Sprite.getPosition().y > window.getSize().y)
            {
                delete *(space.LASERS.begin()+i);
                space.LASERS.erase(space.LASERS.begin() + i);
                break;
            }

            //Enemy collision
            for (unsigned int k = 0; k < OBJECTS.size(); k++)
            {
                if (space.LASERS[i]->Sprite.getGlobalBounds().intersects(OBJECTS[k]->Sprite.getGlobalBounds()))
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

        for (unsigned int k = 0; k < BONUSES.size(); k++)
        {
            BONUSES[k]->render(window);
            BONUSES[k]->animuj(elapsed);
            BONUSES[k]->out_of_screen(window.getSize());
            if(space.getGlobalBounds().intersects(BONUSES[k]->Sprite.getGlobalBounds()))
            {
                space.update_points(10);
                BONUSES[k]->to_center(window.getSize());
            }
        }


        /// tutaj prosze ostroznie


        //wysył kurwa danych
        //        size_t size;
        //        std::string ip = "127.0.0.1";
        //        int port = 2000;
        //        std::vector<std::pair<int, int> > asteroid_speed;
        ////        Proxy proxy(size, ip);
        ////        proxy.Update_Location(space.getRotation(), true, space.getPoints(), asteroid_speed);
        //        SingleFrame request,response;
        //        request = space.getState();
        //        //brakuje vectora predkosci asteroid
        //        //request.asteroids_speed = space. (asteroidy, predkosc vector<pair<int, int>>)
        //        sf::TcpSocket socket;
        //        sf::Socket::Status status = socket.connect("127.0.0.1", 2000);
        //        sf::Packet request_packet, response_packet;
        //            request_packet << request;
        //            if(socket.send(request_packet) == sf::Socket::Done)
        //            {
        //                std::cout<<"Pomyślnie przesłano strukturę"<<std::endl;
        //            }
        //            else
        //            {std::cout<<"niepowodzenie w transmisji danych"<<std::endl;}
        //            sf::sleep(sf::milliseconds(20));
        //        space.isLaser = false;
        //            if(socket.receive(response_packet) == sf::Socket::Status::Done)
        //            {
        //                response_packet << response;
        ////                if (response.client_ID != space.getID()) {
        //                    std::cout<<"rotacja: "<<response.rotation<<std::endl;
        //                    std::cout<< "punkty: "<<response.points<<std::endl;
        //                    std::cout<<"czy laser: " <<response.is_laser<<std::endl;
        //                    std::cout<<"ID: " <<response.client_ID <<std::endl;
        //                    std::cout<<std::endl<<std::endl;
        ////                }
        ////                else
        ////                {std::cout<<"pominięto dane drugiego klienta"<<std::endl;}
        //            }

        //            if (status == sf::Socket::Done)
        //            {
        //                if (socket.send(&request, sizeof(request)) != sf::Socket::Done) {
        //                    std::cout<<"Error while sending current location"<<std::endl;
        //                }
        //
        //            }

        //        wysyłanie rotacji

        //            float pos_x=space.getRotation();
        //
        //            std::cout << space.getRotation()<<std::endl;
        //            //            delete pos_x;
        //            //        socket.connect("127.0.0.1", 2000);
        //            socket.send(&pos_x, sizeof(pos_x));
        //            //        //socket.disconnect();
        //            threshold = 0 ;
        //        }
        window.display();
    }
    /////////////////////////////////////////////////////////
    return 0;
}

