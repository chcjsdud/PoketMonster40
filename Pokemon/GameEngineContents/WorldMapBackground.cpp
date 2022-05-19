#include "WorldMapBackground.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>

WorldMapBackground::WorldMapBackground() 
	: WorldMap1_(nullptr)
	, RoomsRenderer_(nullptr)
	, TestRenderer_(nullptr)
{
}

WorldMapBackground::~WorldMapBackground() 
{
}

void WorldMapBackground::Start()
{
	WorldMap1_ = CreateRenderer("test3.bmp");
	WorldMap1_->SetPivot({1000, -1800});
	RoomsRenderer_ = CreateRenderer("Room.bmp");
	RoomsRenderer_->SetPivot({-2500, 0});

	//TestRenderer_ = CreateRenderer("White.bmp");
	//TestRenderer_->SetPivot({ -3250, -350 });

	AllPosVector.push_back({ -1420, -100 });
	AllPosVector.push_back({ -1150, -350 });
	AllPosVector.push_back({ -3250, -350 });
}

void WorldMapBackground::Update()
{

}