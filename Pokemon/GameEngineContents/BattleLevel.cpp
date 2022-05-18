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
	GameEngineInput::GetInst()->CreateKey("SUp", VK_UP);
	
	CreateActor<BattleBackground>();
	
	BattleInerface* Interface = CreateActor<BattleInerface>(3);
	Interface->SetPosition({ 720.0f, 548.0f });

	Select = CreateActor<BattleSelect>(4);
	Select->SetPosition({ 530.0f,522.0f }); //기본 Fight위치 셋팅
}

void BattleLevel::Update()
{
	if ((Select->GetPosition().x == 530.0f && Select->GetPosition().y == 522.0f) &&true == GameEngineInput::GetInst()->IsDown("SDown"))
	{	//Fight에서 Pokemon으로
		Select->SetPosition({ 530.0f,585.0f });
	}

	if ((Select->GetPosition().x == 530.0f && Select->GetPosition().y == 585.0f) && true == GameEngineInput::GetInst()->IsDown("SUp"))
	{	//Pokemon에서 Fight로
		Select->SetPosition({ 530.0f,522.0f });
	}

	if ((Select->GetPosition().x == 530.0f && Select->GetPosition().y == 522.0f) && true == GameEngineInput::GetInst()->IsDown("SRight"))
	{	//Fight에서 Bag으로
		Select->SetPosition({ 750.0f,522.0f });
	}

	if ((Select->GetPosition().x == 750.0f && Select->GetPosition().y == 522.0f) && true == GameEngineInput::GetInst()->IsDown("SLeft"))
	{	//Bag에서 Fight로
		Select->SetPosition({ 530.0f,522.0f });
	}

	if ((Select->GetPosition().x == 750.0f && Select->GetPosition().y == 522.0f) && true == GameEngineInput::GetInst()->IsDown("SDown"))
	{	//Bag에서 Run으로
		Select->SetPosition({ 750.0f,585.0f });
	}

	if ((Select->GetPosition().x == 750.0f && Select->GetPosition().y == 585.0f) && true == GameEngineInput::GetInst()->IsDown("SUp"))
	{	//Run에서 Bag으로
		Select->SetPosition({ 750.0f,522.0f });
	}

	if ((Select->GetPosition().x == 750.0f && Select->GetPosition().y == 585.0f) && true == GameEngineInput::GetInst()->IsDown("SLeft"))
	{	//Run에서 Pokemon으로
		Select->SetPosition({ 530.0f,585.0f });
	}

	if ((Select->GetPosition().x == 530.0f && Select->GetPosition().y == 585.0f) && true == GameEngineInput::GetInst()->IsDown("SRight"))
	{	//Pokemon에서 Run으로
		Select->SetPosition({ 750.0f,585.0f });
	}
} 

