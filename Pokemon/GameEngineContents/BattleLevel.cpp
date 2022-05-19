#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

#include "BattleLevel.h"
#include "BattleUnitRenderer.h"
#include "BattleBackground.h"



BattleLevel::BattleLevel()
{

}

BattleLevel::~BattleLevel()
{

}

void BattleLevel::Loading()
{
	CreateActor<BattleBackground>();
	CreateActor<BattleUnitRenderer>();

	Interface = CreateActor<BattleInerface>(3);
	Interface->SetPosition({ 720.0f, 548.0f });

	Interface->GetSelect()->SetPivot({ -190.0f, -25.0f });
	Interface->GetEnemyHPUI()->SetPivot({ -450.0f,-430.0f });
	Interface->GetMyHPUI()->SetPivot({ 0.0f,-170.0f });

}

void BattleLevel::Update()
{
} 

