#include "WorldMapBackground.h"

WorldMapBackground::WorldMapBackground() 
{
}

WorldMapBackground::~WorldMapBackground() 
{
}

void WorldMapBackground::Start()
{
	CreateRenderer("test.bmp");
	CreateRenderer("test2.bmp");
}

