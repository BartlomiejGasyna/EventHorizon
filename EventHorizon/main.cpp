#include "EventHorizon.h"
#include "abstract.h"
#include "asteroid1.h"
#include "spaceship_new.hpp"
#include "laser.h"
#include "IP_proxy.hpp"

SingleFrame last_response;

sf::Packet& operator << (sf::Packet& packet, const SingleFrame &frame)
{
    return packet << frame.rotation << frame.is_laser << frame.points;
}
    
sf::Packet& operator >> (sf::Packet& packet, SingleFrame &frame)
{
    return packet >> frame.rotation >> frame.is_laser >> frame.points;
}
    
int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window");
    
    //loading textures, creating objects
    //char data[100];
    std::string data[100];
    sf::Texture texture_spaceship;
    if(!texture_spaceship.loadFromFile("Spaceship2.png")) { std::cout<<"error"; }
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
    
    
    //tutaj jest nowej klasy spaceship_new
    Spaceship_new space(0, 0, texture_spaceship, 0,0, window);

    std::cout<<space.getOrigin().x<<"  "<<space.getOrigin().y<<std::endl;
    std::cout<<space.getPosition().x<<"  "<<space.getPosition().y<<std::endl;

    sf::Texture texture_doge;
    if(!texture_doge.loadFromFile("doge.png")) { std::cout<<"error"; }
    
    sf::Texture texture_asteroid;
    if(!texture_asteroid.loadFromFile("owoc.png")) { std::cout<<"error"; }

    std::vector<Abstract*> ASTEROIDY;

    for (int i = 0; i < 25; i++)
    {
        ASTEROIDY.push_back(new Asteroid1(0, 0, &texture_asteroid));
        ASTEROIDY[i]->to_center(window.getSize());
    }
    
    float spaceship_angular_velocity = 50;
    
    //BACKGROUND
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sf::Texture texture_background;
    if(!texture_background.loadFromFile("background base.png")) { std::cout<<"error";
    }
    sf::Texture texture_background2;
    if(!texture_background2.loadFromFile("background base2.png")) { std::cout<<"error";
    }
    Background background1(texture_background, 0.0, 0.0, window);
    Background background2(texture_background2, 0.0, 0.0, window);
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
                    space.LASERS.push_back(new Laser(&texture_doge, space.getGlobalBounds().left+space.getGlobalBounds().width/2, space.getGlobalBounds().top+space.getGlobalBounds().width/2, space.getRotation()));
                    threshold = 0;
                    space.isLaser = true;
                }
                space.isLaser = false;
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

        background1.rotate(-0.05);
        background2.rotate(0.05);
        window.draw(background1);
        window.draw(background2);

        window.draw(space);
        space.animuj(elapsed, full_time);


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
            for (unsigned int k = 0; k < ASTEROIDY.size(); k++)
            {
                if (space.LASERS[i]->Sprite.getGlobalBounds().intersects(ASTEROIDY[k]->Sprite.getGlobalBounds()))
                {
                    if (ASTEROIDY[k]->HP <= 0)
                    {
                        //ASTEROIDY[i]->to_center(window.getSize());
                        // ASTEROIDY.erase(ASTEROIDY.begin()+i);
                        ASTEROIDY[k]->to_center(window.getSize());
                        std::cout<<"ASTEORIDA PADA KURWAAAAAAAAAAAAAAA"<<std::endl;

                    }
                    else ASTEROIDY[k]->HP--;
                    space.update_points(1);
                    space.LASERS.erase(space.LASERS.begin() + i);
                }
            }
        }

        //TA PĘTLA OBSŁUGUJE KOLIZJE
        for (unsigned int i = 0; i < ASTEROIDY.size(); i++)
        {
            ASTEROIDY[i]->render(window);
            ASTEROIDY[i]->animuj(elapsed);
            ASTEROIDY[i]->out_of_screen(window.getSize());
           // ASTEROIDY[i]->getVelocities();
            //std::cout<<"no collision"<<std::endl;

            if(space.getGlobalBounds().intersects(ASTEROIDY[i]->Sprite.getGlobalBounds()))
            {
                ASTEROIDY[i]->to_center(window.getSize());
                std::cout<<"collision" << std::endl;
            }
        }
        
        
        /// tutaj prosze ostroznie
        
        if(threshold > 200)
        {
        //wysył kurwa danych
        size_t size;
        std::string ip = "127.0.0.1";
        int port = 2000;
        std::vector<std::pair<int, int> > asteroid_speed;
//        Proxy proxy(size, ip);
//        proxy.Update_Location(space.getRotation(), true, space.getPoints(), asteroid_speed);
        SingleFrame request,response;
        request.rotation = space.getRotation();
        request.is_laser = space.isLaser;
        request.points = space.getPoints();
        //brakuje vectora predkosci asteroid
        //request.asteroids_speed = space. (asteroidy, predkosc vector<pair<int, int>>)
        
        sf::TcpSocket socket;
        sf::Socket::Status status = socket.connect("127.0.0.1", 2000);
            sf::Packet request_packet;
            request_packet << request;
            if(socket.send(request_packet) == sf::Socket::Done)
            {
                std::cout<<"Pomyślnie przesłano strukturę"<<std::endl;
            }
            else
            {std::cout<<"niepowodzenie w transmisji danych"<<std::endl;}
    
            
//            if (status == sf::Socket::Done)
//            {
//                if (socket.send(&request, sizeof(request)) != sf::Socket::Done) {
//                    std::cout<<"Error while sending current location"<<std::endl;
//                }
//
//            }
            threshold = 0;
        }
        
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
