#include <arpa/inet.h>  // inet_pton()
#include <stdio.h>
#include <stdlib.h>  // exit()
#include <string.h>  // memset()
#include <sys/socket.h>

#include <thread>

#include "../InternalLib/MessageInterface/src/MessageInterface.hpp"
#include "../InternalLib/MessageInterface/src/MovePacket.hpp"
#include "../InternalLib/MessageInterface/src/Packet.hpp"
#include "../InternalLib/MessageInterface/src/PingPacket.hpp"
#include "../InternalLib/MessageInterface/src/SayPacket.hpp"
#include "../headers/pch.hpp"

#define SERWER_PORT 8888
#define SERWER_IP   "127.0.0.1"

// ONLY FOR TESTS.........!!!!!!!
void ProssedReceiveMsg (unsigned char *recArray, const int &size)
{
	MsgInterface::MsgType msgType       = static_cast<MsgInterface::MsgType> (recArray [0]);
	size_t                sizeOfPackage = MsgInterface::GetSizeOfPackageByMsgType (msgType);

	PingPacket pp;

	MsgInterface::BytesToVar (recArray, pp);

	// std::cout << "Client Send: " << std::endl;
	std::cout << "ping: " << pp.ping << std::endl;
	// std::cout << "sp.type : " << PrintMsgType (sp.type) << std::endl;

	/*
	for (int i = 0; i < size; ++i)
	{
		if (recArray [i] > 0)
		{
			MsgInterface::MsgType msgType       = static_cast<MsgInterface::MsgType> (recArray [i]);
			size_t                sizeOfPackage = MsgInterface::GetSizeOfPackageByMsgType (msgType);

			if (i == 0)
			{
				// PROCESS receive

				unsigned char objArr [sizeOfPackage];

				for (size_t j = 0; j < sizeOfPackage; ++j) { objArr [j] = recArray [j]; }

				MovePacket mpClient;

				MsgInterface::BytesToVar (objArr, mpClient);
				i += sizeOfPackage - 1;
				// std::cout << "Client Ping: " << mpClient.ping << std::endl;

				std::cout << "Client Send: " << std::endl;
				std::cout << "mp.entity: " << mpClient.entity << std::endl;
				std::cout << "mp.type : " << PrintMsgType (mpClient.type) << std::endl;
				std::cout << "mp.x: " << mpClient.x << std::endl;
				std::cout << "mp.y: " << mpClient.y << std::endl;
				std::cout << "mp.z: " << mpClient.z << std::endl;

				continue;
			}
			else
			{
				unsigned char objArr [sizeOfPackage];

				for (size_t j = 0; j < sizeOfPackage; ++j) { objArr [j] = recArray [j + i]; }

				PingPacket pp;

				MsgInterface::BytesToVar (objArr, pp);

				// std::cout << "Client Send: " << std::endl;
				std::cout << "ping: " << pp.ping << std::endl;
				// std::cout << "sp.type : " << PrintMsgType (sp.type) << std::endl;

				i += sizeOfPackage - 1;
			}
		}
		else
		{
			// cant receive package
			break;
		}
	}*/
}

/*
	odbieranie,
	kazy pakiet w 1 bajcie ma command po którym mozna zidentyfikowac całyh pakie, a gdy wiemy jaki to pakiet to rozmiar
   odebrajen wiadomosci to sizeof

	mozna odebrac wiele wiadomosci jednoczesnie,

*/

int main( )
{
	struct sockaddr_in serwer = {.sin_family = AF_INET, .sin_port = htons (SERWER_PORT)};
	if (inet_pton (AF_INET, SERWER_IP, &serwer.sin_addr) <= 0)
	{
		perror ("inet_pton() ERROR");
		exit (1);
	}

	const int socket_ = socket (AF_INET, SOCK_DGRAM, 0);
	if ((socket_) < 0)
	{
		perror ("socket() ERROR");
		exit (2);
	}

	socklen_t len = sizeof (serwer);
	if (bind (socket_, (struct sockaddr *) &serwer, len) < 0)
	{
		perror ("bind() ERROR");
		exit (3);
	}

	// IF ALL ABOUT TO WRITE SO, HOW THIS LOOKING ITS NOT MATTER...
	bool isInfoShow = false;

	while (1)
	{
		struct sockaddr_in client = { };

		if (!isInfoShow) std::cout << "Waiting for connection...\n";

		// printf ();

		// Packet packet;

		// unsigned char SendArrayByteMsg [MsgInterface::MSG_SIZE];

		std::unique_ptr<Packet> packet = std::make_unique<Packet>( );

		if (recvfrom (socket_, (void *) packet.get( ), sizeof (Packet), 0, (struct sockaddr *) &client, &len) < 0)
		{
			perror ("recvfrom() ERROR");
			exit (4);
		}

		if (!isInfoShow)
		{
			std::cout << "New connection , socket fd is" << socket_ << ", ip is :" << inet_ntoa (client.sin_addr)
					  << " , port : " << ntohs (client.sin_port) << "\n";

			isInfoShow = true;
		}

		/*
				std::vector<unsigned char> vectorMessage;

				for (uint32_t i = 0; i < MsgInterface::MSG_SIZE; ++i)
				{
					unsigned char byte = SendArrayByteMsg [i];
					if (byte == MsgInterface::endMsgFirst && SendArrayByteMsg [i + 1] == MsgInterface::endMsgSecond)
					{
						vectorMessage.push_back (byte);
						vectorMessage.push_back (SendArrayByteMsg [i + 1]);
						break;
					}

					vectorMessage.push_back (byte);
				}

				ProssedReceiveMsg (SendArrayByteMsg, len);*/

		// MsgInterface::BytesToVar (vectorMessage, packet);

		PingPacket pp;

		std::vector<unsigned char> vectorMessage;

		for (size_t i = 0; i <= packet->data.size( ); ++i)
		{
			MsgInterface::MsgType msgType       = static_cast<MsgInterface::MsgType> (packet->data.at (0));
			size_t                sizeOfPackage = MsgInterface::GetSizeOfPackageByMsgType (msgType);

			for (size_t y = 0; y < sizeOfPackage; y++) { vectorMessage.push_back (packet->data.at (y)); }
			break;  // for now, untill i write server
		}

		MsgInterface::BytesToVar (vectorMessage, pp);

		std::cout << "Client Send: " << std::endl;
		std::cout << "ping: " << pp.ping << std::endl;
		std::cout << "Resend this ping to client " << std::endl;

		Packet pac;
		pac.data = packet->data;
		// pac.eof  = packet->eof;
		pac.size = packet->size;

		// send back same msg to client
		if (sendto (socket_, (void *) &pac, sizeof (Packet), 0, (struct sockaddr *) &client, len) < 0)
		{
			perror ("sendto() ERROR");
			exit (5);
		}

		// char buffer_ip [128] = { };
		// printf ("|Client ip: %s port: %d|\n", inet_ntop (AF_INET, &client.sin_addr, buffer_ip, sizeof (buffer_ip)),
		//		ntohs (client.sin_port));
	}

	shutdown (socket_, SHUT_RDWR);
}
// gcc server.c -g -Wall -o server && ./server
