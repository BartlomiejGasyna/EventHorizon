
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
//    char client_id;
    int client_ID;
    // to trzeba bedzie dodac
    //std::vector<std::pair<int, int>>asteroids_speed;
    
};

sf::Packet& operator << (sf::Packet& packet, const SingleFrame &frame)
{
    return packet << frame.rotation << frame.is_laser << frame.points<<frame.client_ID;
}
    
sf::Packet& operator >> (sf::Packet& packet, SingleFrame &frame)
{
    return packet >> frame.rotation >> frame.is_laser >> frame.points << frame.client_ID;
}
    

SingleFrame client1;
int main(int, char const**)
{
    
    
    // Create the main window
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
        SingleFrame client1;
//        std::cout<<elapsed.asMicroseconds()<<std::endl;
        listener.accept(socket);
        
        //socket.receive(&client1, sizeof(client1), received);
        if (socket.receive(packet) == sf::Socket::Status::Done) {
            std::cout<<"udalo sie odebrac strukture"<<std::endl;
//            if (client1.client_ID == 1)
//            {
//                std::cout<<"Gracz 1: "<<std::endl;
//            }
//            else if (client1.client_ID == 2)
//            {
//                std::cout<<"Gracz 2: "<<std::endl;
//            }
            if (packet >> client1 ) {
                std::cout<<"rotacja: "<<client1.rotation<<std::endl;
                std::cout<< "punkty: "<<client1.points<<std::endl;
                std::cout<<"czy laser: " <<client1.is_laser<<std::endl;
                std::cout<<"ID: " <<client1.client_ID <<std::endl;
                std::cout<<std::endl<<std::endl;
            }
        
        else
            std::cout<<"BŁĄD!"<<std::endl;
        if(socket.send(packet) == sf::Socket::Done)
        {
            std::cout<<"przesłano dane"<<std::endl;
        }
            
        sf::sleep(sf::milliseconds(20));
    }
    }
   
    

    return EXIT_SUCCESS;
}
