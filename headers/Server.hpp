#ifndef SERVER
#define SERVER

#include <arpa/inet.h>  // inet_pton()
#include <stdio.h>
#include <stdlib.h>  // exit()
#include <string.h>  // memset()
#include <sys/socket.h>

#include "INetValue.hpp"
#include "IServer.hpp"
#include "pch.hpp"

class Server
	: public IServer
	, public INetValue
{
	struct sockaddr_in* m_ServerAddr;
	socklen_t           m_ServerAddrLen;
	int                 m_socket {-1};

   public:
	Server( );
	~Server( );

	void            Create (const char* ip, const int& port) override;
	const int&      GetSocket( ) override;
	const uint32_t& GetAdrLenght( ) override;
	void            CreateSocket( ) override;
	void            BindSocket( ) override;
};

#endif  // SERVER