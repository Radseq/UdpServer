#ifndef ISERVER
#define ISERVER

#include "pch.hpp"

class IServer
{
   public:
	virtual ~IServer( ) { }
	virtual void Create (const char* ip, const int& port) = 0;
	virtual void CreateSocket( )                          = 0;
	virtual void BindSocket( )                            = 0;
};

#endif  // ISERVER