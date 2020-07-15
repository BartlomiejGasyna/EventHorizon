
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

sf::Packet& operator << (sf::Packet& packet, SingleFrame &frame)
{
    return packet << frame.rotation << frame.is_laser << frame.points <<frame.client_ID;
}
    
sf::Packet& operator >> (sf::Packet& packet, SingleFrame &frame)
{
    return packet >> frame.rotation >> frame.is_laser >> frame.points >>frame.client_ID;
}
    

SingleFrame client1;
int main(int, char const**)
{
    
    
    // Create the main window
    sf::TcpSocket socket;
    socket.connect("127.0.0.1", 2000);
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
        sf::Packet packet, response;
        SingleFrame client, temp_response;
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
            if (packet >> client ) {
                std::cout<<"rotacja: "<<client.rotation<<std::endl;
                std::cout<< "punkty: "<<client.points<<std::endl;
                std::cout<<"czy laser: " <<client.is_laser<<std::endl;
                std::cout<<"ID: " <<client.client_ID <<std::endl;
                std::cout<<std::endl<<std::endl;
                
                temp_response.rotation = client.rotation;
                temp_response.points = client.points;
                temp_response.is_laser = client.is_laser;
                temp_response.client_ID = client.client_ID;
                response << temp_response;
            }
            
        
        else
            std::cout<<"BŁĄD!"<<std::endl;
            //response = packet;
            
        if(socket.send(response) == sf::Socket::Done)
        {
            std::cout<<"przesłano dane gracza nr: "<< client.client_ID<<std::endl<<std::endl;
        }
            
//        sf::sleep(sf::milliseconds(10));
    }
    }
   
    

    return EXIT_SUCCESS;
}
