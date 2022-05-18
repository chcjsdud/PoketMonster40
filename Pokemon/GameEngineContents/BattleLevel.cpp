#include <GameEngineBase/GameEngineInput.h>

#include "BattleLevel.h"
#include "BattleBackground.h"
#include "BattleInerface.h"


BattleLevel::BattleLevel()
{

}

BattleLevel::~BattleLevel()
{

}

void BattleLevel::Loading()
{
	GameEngineInput::GetInst()->CreateKey("SLeft", VK_LEFT);
	GameEngineInput::GetInst()->CreateKey("SRight", VK_RIGHT);
	GameEngineInput::GetInst()->CreateKey("SDown", VK_DOWN);
	
	
	CreateActor<BattleBackground>();
	
	BattleInerface* Interface = CreateActor<BattleInerface>(3);
	Interface->SetPosition({ 720.0f, 548.0f });

	Select = CreateActor<BattleSelect>(4);
	Select->SetPosition({ 530.0f,522.0f }); //기본 Fight위치 셋팅
}

void BattleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("SDown"))
	{
		Select->SetPosition({ 530.0f,585.0f });
	}
}

