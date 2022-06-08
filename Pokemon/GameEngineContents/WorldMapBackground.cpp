#include "WorldMapBackground.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>

#include "PlayerRed.h"

WorldMapBackground::WorldMapBackground() 
	: WorldMap1_(nullptr)
	, WorldMap2_(nullptr)
	, WorldMap3_(nullptr)
	, RoomsRenderer_(nullptr)
	, Rooms2Renderer_(nullptr)
{
}

WorldMapBackground::~WorldMapBackground() 
{
}

void WorldMapBackground::Start()
{
	WorldMap1_ = CreateRenderer("WorldMap1.bmp");
	WorldMap1_->SetPivot({1000, -1800});
	WorldMap2_ = CreateRenderer("WorldMap2.bmp");
	WorldMap2_->SetPivot({ -2525, -3993 });
	WorldMap3_ = CreateRenderer("WorldMap3.bmp");
	WorldMap3_->SetPivot({ 885, -9491 });
	RoomsRenderer_ = CreateRenderer("Rooms1.bmp");
	RoomsRenderer_->SetPivot({-2500, 0});
	Rooms2Renderer_ = CreateRenderer("Rooms2.bmp");
	Rooms2Renderer_->SetPivot({ -5800, 0 });
	GymRenderer_ = CreateRenderer("Gym.bmp");
	GymRenderer_->SetPivot({-2500, -6500});
}

void WorldMapBackground::Update()
{

}