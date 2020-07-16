#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>


struct SingleFrame
{
    float rotation;
    bool is_laser;
    int points;
    int client_ID;
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
    sf::TcpListener listener;
    if (listener.listen(2000) == sf::Socket::Done) {
        std::cout<<"serwer nawiązał połączenie"<<std::endl;
    }
    

    for(;;)
    {

        
        sf::Packet packet, response;
        SingleFrame client, Frame_client1, Frame_client2;

        listener.accept(socket);

        if (socket.receive(packet) == sf::Socket::Status::Done) {
            std::cout<<"udalo sie odebrac strukture"<<std::endl;
            if (packet >> client ) {
                std::cout<<"rotacja: "<<client.rotation<<std::endl;
                std::cout<< "punkty: "<<client.points<<std::endl;
                std::cout<<"czy laser: " <<client.is_laser<<std::endl;
                std::cout<<"ID: " <<client.client_ID <<std::endl;
                
                if (client.client_ID == 1) {
                    Frame_client1 = client;
                    response << Frame_client2;
                    if(socket.send(response) == sf::Socket::Done)
                    {
                        std::cout<<"przesłano dane gracza nr: "<< client.client_ID<<std::endl<<std::endl<<std::endl;
                    }
                    else
                    {
                        std::cout<<"błąd w przysle danych gracza : "<< client.client_ID<<std::endl<<std::endl<<std::endl;
                    }
                        
                }
                else if (client.client_ID == 2)
                {
                    Frame_client2 = client;
                    response << Frame_client1;
                    if(socket.send(response) == sf::Socket::Done)
                    {
                        std::cout<<"przesłano dane gracza nr: "<< client.client_ID<<std::endl<<std::endl;
                    }
                }
                
            }
        else
            std::cout<<"BŁĄD!"<<std::endl;
    }
    }
   
    

    return EXIT_SUCCESS;
}
