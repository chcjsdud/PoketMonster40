#include "BattleInerface.h"
#include <GameEngineBase/GameEngineInput.h>

BattleInerface::BattleInerface()
{

}

BattleInerface::~BattleInerface()
{

}

void BattleInerface::Start()
{
	GameEngineInput::GetInst()->CreateKey("SLeft", VK_LEFT);
	GameEngineInput::GetInst()->CreateKey("SRight", VK_RIGHT);
	GameEngineInput::GetInst()->CreateKey("SDown", VK_DOWN);
	GameEngineInput::GetInst()->CreateKey("SUp", VK_UP);
	GameEngineInput::GetInst()->CreateKey("SSelect", 'A');


	InterfaceImage = CreateRenderer("Battle_Select.bmp",0);
	
	Select = CreateRenderer("Select.bmp", 1);

	//MyHPUI = CreateRenderer("FriendlyHPBackground.bmp",1);
	//EnemyHPUI = CreateRenderer("EnemyHPBackground.bmp",1);
}

void BattleInerface::Render()
{
}

void BattleInerface::Update()
{
	MoveKey();
}


void BattleInerface::MoveKey()
{
	if ((GetSelect()->GetPivot().x == -190.0f && GetSelect()->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SDown"))
	{	//Fight에서 Pokemon으로
		GetSelect()->SetPivot({ -190.0f,35.0f });
	}

	if ((GetSelect()->GetPivot().x == -190.0f && GetSelect()->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SUp"))
	{	//Pokemon에서 Fight로
		GetSelect()->SetPivot({ -190.0f,-25.0f });
	}

	if ((GetSelect()->GetPivot().x == -190.0f && GetSelect()->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SRight"))
	{	//Fight에서 Bag으로
		GetSelect()->SetPivot({ 30.0f,-25.0f });
	}

	if ((GetSelect()->GetPivot().x == 30.0f && GetSelect()->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SLeft"))
	{	//Bag에서 Fight로
		GetSelect()->SetPivot({ -190.0f,-25.0f });
	}

	if ((GetSelect()->GetPivot().x == 30.0f && GetSelect()->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SDown"))
	{	//Bag에서 Run으로
		GetSelect()->SetPivot({ 30.0f,35.0f });
	}

	if ((GetSelect()->GetPivot().x == 30.0f && GetSelect()->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SUp"))
	{	//Run에서 Bag으로
		GetSelect()->SetPivot({ 30.0f,-25.0f });
	}

	if ((GetSelect()->GetPivot().x == -190.0f && GetSelect()->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SRight"))
	{	//Pokemon에서 Run으로
		GetSelect()->SetPivot({ 30.0f,35.0f });
	}

	if ((GetSelect()->GetPivot().x == 30.0f && GetSelect()->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SLeft"))
	{	//Run에서 Pokemon으로
		GetSelect()->SetPivot({ -190.0f,35.0f });
	}
}