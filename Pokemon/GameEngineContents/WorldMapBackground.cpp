#include "WorldMapBackground.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>

WorldMapBackground::WorldMapBackground() 
	: WorldMap1_(nullptr)
	, RoomsRenderer_(nullptr)
	, Rooms2Renderer_(nullptr)
{
}

WorldMapBackground::~WorldMapBackground() 
{
}

void WorldMapBackground::Start()
{
	//WorldMap1_ = CreateRenderer("Test3.bmp");
	WorldMap1_ = CreateRenderer("Test3_NoFlower.bmp");
	WorldMap1_->SetPivot({1000, -1800});
	RoomsRenderer_ = CreateRenderer("Rooms1.bmp");
	RoomsRenderer_->SetPivot({-2500, 0});
	Rooms2Renderer_ = CreateRenderer("Rooms2.bmp");
	Rooms2Renderer_->SetPivot({ -5800, 0 });
}

void WorldMapBackground::Update()
{

}