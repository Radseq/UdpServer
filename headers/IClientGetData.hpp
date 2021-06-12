#ifndef ICLIENT_GET_DATA
#define ICLIENT_GET_DATA

#include "pch.hpp"

class IClientGetData
{
   public:
	virtual ~IClientGetData( ) { }
	virtual void GetData (void* data, const size_t& size) = 0;
};

#endif  // ICLIENT_GET_DATA