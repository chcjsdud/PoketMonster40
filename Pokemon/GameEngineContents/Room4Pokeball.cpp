#include "Room4Pokeball.h"

Room4Pokeball::Room4Pokeball() 
	: Renderer_(nullptr)
{
}

Room4Pokeball::~Room4Pokeball() 
{
}

void Room4Pokeball::Start()
{
	Renderer_ = CreateRenderer("Room4Pokeball.bmp");
}

