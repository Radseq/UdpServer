#ifndef INET_VALUE
#define INET_VALUE

#include "pch.hpp"

class INetValue
{
   public:
	virtual ~INetValue( ) { }
	virtual const int&      GetSocket( )    = 0;
	virtual const uint32_t& GetAdrLenght( ) = 0;
};

#endif  // INET_VALUE