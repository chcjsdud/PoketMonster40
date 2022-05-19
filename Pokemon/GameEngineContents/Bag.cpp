#include "Bag.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Bag::Bag() 
{
}

Bag::~Bag() 
{
}

void Bag::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	CreateRenderer("Bag_Back.bmp");

	BagRedrerer_ = CreateRenderer("Bag_LeftOpen.bmp");
	BagRedrerer_->SetPivot({-320, 0});
}

void Bag::Update()
{
}

void Bag::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Bag::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
