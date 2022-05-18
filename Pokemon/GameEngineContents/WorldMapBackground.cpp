#include "WorldMapBackground.h"
#include <GameEngine/GameEngineRenderer.h>

WorldMapBackground::WorldMapBackground() 
{
}

WorldMapBackground::~WorldMapBackground() 
{
}

void WorldMapBackground::Start()
{
	WorldMap1_ = CreateRenderer("test3.bmp");
	WorldMap1_->SetPivot({1000, -1800});
	CreateRenderer("test2.bmp");
}

