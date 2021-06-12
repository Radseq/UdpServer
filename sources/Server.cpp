#include "../headers/Server.hpp"

#include "../headers/pch.hpp"

Server::Server( ) { }

Server::~Server( ) { }

void Server::Create (const char* ip, const int& port)
{
	try
	{
		m_ServerAddr    = new sockaddr_in {.sin_family = AF_INET, .sin_port = htons (port)};
		m_ServerAddrLen = sizeof (m_ServerAddr);

		int result = inet_pton (AF_INET, ip, &m_ServerAddr->sin_addr);
		if (result <= 0) { throw "inet_pton error"; }
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what( ) << std::endl;
	}
}

void Server::CreateSocket( )
{
	try
	{
		m_socket = socket (AF_INET, SOCK_DGRAM, 0);
		if ((m_socket) < 0) { throw "socket() ERROR"; }
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what( ) << std::endl;
	}
}

void Server::BindSocket( )
{
	try
	{
		if (bind (m_socket, (struct sockaddr*) &m_ServerAddr, m_ServerAddrLen) < 0) { throw "bind() ERROR"; }
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what( ) << std::endl;
	}
}
/*
void Server::Receive (void* data)
{
	try
	{
		const auto result =
			1;  //= recvfrom (m_socket, data, sizeof (data), 0, (struct sockaddr*) &client, &m_ServerAddrLen);
		if (result < 0) { perror ("recvfrom() ERROR"); }
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what( ) << std::endl;
	}
}*/

const int&      Server::GetSocket( ) { return m_socket; }
const uint32_t& Server::GetAdrLenght( ) { return m_ServerAddrLen; }