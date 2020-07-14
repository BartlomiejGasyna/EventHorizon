
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>

struct SingleFrame
{
    float rotation;
    bool is_laser;
    int points;
    // to trzeba bedzie dodac
    //std::vector<std::pair<int, int>>asteroids_speed;
    
};

sf::Packet& operator << (sf::Packet& packet, const SingleFrame &frame)
{
    return packet << frame.rotation << frame.is_laser << frame.points;
}
    
sf::Packet& operator >> (sf::Packet& packet, SingleFrame &frame)
{
    return packet >> frame.rotation >> frame.is_laser >> frame.points;
}
    

SingleFrame client1;
int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::TcpSocket socket;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    
    
   // listener.setBlocking(false);
    std::string text = "\njestem na serwerze";
    socket.send(&text, text.size());
//    socket.disconnect();
    
    
    sf::TcpListener listener;
    listener.listen(2000);
    
    if (listener.listen(2000) == sf::Socket::Done) {
        std::cout<<"serwer nawiązał połączenie"<<std::endl;
    }
    
//    socket.disconnect();
    for(;;)
    {
        sf::Packet packet;
        SingleFrame response;
//        std::cout<<elapsed.asMicroseconds()<<std::endl;
        listener.accept(socket);
        size_t received;
        //socket.receive(&client1, sizeof(client1), received);
        if (socket.receive(packet) == sf::Socket::Status::Done) {
            std::cout<<"udalo sie odebrac strukture"<<std::endl;
            if (packet >> response ) {
                std::cout<<"rotacja: "<<response.rotation<<std::endl;
                std::cout<< "punkty: "<<response.points<<std::endl;
                std::cout<<"czy laser: " <<response.is_laser<<std::endl;
                std::cout<<std::endl<<std::endl;
            }
        }
        else
            std::cout<<"BŁĄD!"<<std::endl;
//        std::cout<<"rotacja: "<<client1.rotation<<std::endl;
//        std::cout<< "punkty: "<<client1.points<<std::endl;
//        std::cout<<"czy laser: " <<client1.is_laser<<std::endl;
//        std::cout<<std::endl<<std::endl;
//        clock.restart();

//    }
    
        
        sf::sleep(sf::milliseconds(200));
    }
   
    

    return EXIT_SUCCESS;
}
