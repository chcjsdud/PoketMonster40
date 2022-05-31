#include "Pokemon.h"

Pokemon::Pokemon() 
	: MyInfo_(nullptr)
{
}

Pokemon::~Pokemon() 
{
	if (nullptr != MyInfo_)
	{
		delete MyInfo_;
		MyInfo_ = nullptr;
	}
}

