#include "Bush.h"

Bush::Bush() 
	: Renderer_(nullptr)
{
}

Bush::~Bush() 
{
}

void Bush::Start()
{
	Renderer_ = CreateRenderer("Bush.bmp", 1);
}