#include "Bag.h"
#include <GameEngineBase/GameEngineWindow.h>

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
