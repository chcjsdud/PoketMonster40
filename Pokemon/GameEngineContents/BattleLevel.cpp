#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

#include "BattleLevel.h"
#include "BattleUnitRenderer.h"
#include "BattleBackground.h"
#include "BattleEngine.h"



BattleLevel::BattleLevel()
	: Interface(nullptr)
	, BState_(BattleState::Openning)
	, OpenningEnd_(false)
	, EnddingEnd_(false)
	, PlayerRed_(nullptr)
	, BEngine_(nullptr)
{

}

BattleLevel::~BattleLevel()
{

}

void BattleLevel::Loading()
{
	CreateActor<BattleBackground>();
	CreateActor<BattleUnitRenderer>();
	BEngine_ = CreateActor<BattleEngine>();

	Interface = CreateActor<BattleInerface>(3);
	Interface->SetPosition({ 720.0f, 548.0f });
}

void BattleLevel::Update()
{
	switch (BState_)
	{
	case BattleState::Openning:
		if (OpenningEnd_ == true)
		{
			BState_ = BattleState::Selecet;
		}
		return;
		break;
	case BattleState::Selecet:
		Interface->MoveKey();
		break;
	case BattleState::Battle:
		return;
		break;
	case BattleState::Endding:
		if (EnddingEnd_ == true)
		{
			// 레벨 이동
			return;
		}
		break;
	}
} 


void BattleLevel::LevelChangeStart(GameEngineLevel * _PrevLevel)
{
	if (PlayerRed_ == nullptr)
	{
		PlayerRed_  = PlayerRed::MainRed_;
	}
	//BState_ = BattleState::Openning
	BState_ = BattleState::Selecet;
	OpenningEnd_ = false;
	EnddingEnd_ = false;
	ShowOpenning();
}

void BattleLevel::ShowOpenning()
{

}


void BattleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	OpenningEnd_ = false;
	EnddingEnd_ = false;
}

void BattleLevel::ShowEndding()
{

}