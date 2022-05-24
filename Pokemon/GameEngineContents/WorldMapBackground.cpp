#include "WorldMapBackground.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Flower.h"

WorldMapBackground::WorldMapBackground() 
	: WorldMap1_(nullptr)
	, RoomsRenderer_(nullptr)
{
}

WorldMapBackground::~WorldMapBackground() 
{
}

void WorldMapBackground::Start()
{
	WorldMap1_ = CreateRenderer("Test3_NoFlower.bmp");
	WorldMap1_->SetPivot({1000, -1800});
	RoomsRenderer_ = CreateRenderer("Room.bmp");
	RoomsRenderer_->SetPivot({-2500, 0});
}

void WorldMapBackground::Update()
{

}