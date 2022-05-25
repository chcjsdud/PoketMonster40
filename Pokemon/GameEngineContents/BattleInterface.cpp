#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "BattleInterface.h"
#include "BattleLevel.h"
#include "PokemonEngine.h"
#include "BattleEngine.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include "BattleUnitRenderer.h"

BattleInterface::BattleInterface()
	:TimeCheck(0.0f)
	,CurOrder(BattleOrder::None)
	, InterfaceImage(nullptr)
	, Select(nullptr)
	, MyHPUI(nullptr)
	, EnemyHPUI(nullptr)
	, MyHP(nullptr)
	, EnemyHP(nullptr)
	, EXP(nullptr)
	, BattleCommend(nullptr)
	, MainInterface(nullptr)
	, DownFont_(nullptr)
	, Level_(nullptr)
	, PlayerStopCheck(nullptr)
	, OneTalk(false)
	, Fonts(nullptr)
	, PlayerEnd(false)
{

}

BattleInterface::~BattleInterface()
{

}

void BattleInterface::Start()
{
	// 레벨 생성
	Level_ = dynamic_cast<BattleLevel*>(GetLevel());
	// 폰트 생성
	DownFont_ = Level_->CreateActor<GameEngineContentFont>(10);
	DownFont_->SetPosition({ 50, 485 });
	// 키 생성
	GameEngineInput::GetInst()->CreateKey("SLeft", VK_LEFT);
	GameEngineInput::GetInst()->CreateKey("SRight", VK_RIGHT);
	GameEngineInput::GetInst()->CreateKey("SDown", VK_DOWN);
	GameEngineInput::GetInst()->CreateKey("SUp", VK_UP);
	GameEngineInput::GetInst()->CreateKey("SSelect", 'Z');
	GameEngineInput::GetInst()->CreateKey("SCancel", 'X');
	//

	InterfaceImage = CreateRenderer("Battle_Select.bmp",2);
	
	Select = CreateRenderer("Select.bmp", 3);

	MyHPUI = CreateRenderer("FriendlyHPBackground4.bmp",2);
	EnemyHPUI = CreateRenderer("EnemyHPBackground4.bmp",2);
	MyHP = CreateRenderer("FriendlyHPBar4.bmp", 3);
	EnemyHP = CreateRenderer("EnemyHPBar4.bmp", 3);
	EXP = CreateRenderer("FriendlyHPExp4.bmp", 3);
	BattleCommend = CreateRenderer("BattleCommend4.bmp", 4);
	//Player = CreateRenderer("Player.bmp",0);

	//=========랜더러 위치 설정==========//
	Select->SetPivot({ -190.0f, -25.0f });

	MyHPUI->SetPivot({ 0.0f,-170.0f });
	EnemyHPUI->SetPivot({ -450.0f,-430.0f });
	EnemyHP->SetPivot({ -406.0f,-430.0f });
	MyHP->SetPivot({ 80.0f, -170.0f });
	EXP->SetPivot({48.0f,-170.0f});
	BattleCommend->SetPivot({-240.0f,0.0f});
	BattleCommend->Off();//배틀커맨드는 Fight상태일때만
	//Player->SetPivot({ -450.0f,-180.0f });//멈출위치

	//김예나:테스트 코드
	PlayerStopCheck = Level_->CreateActor<BattleUnitRenderer>();
	Fonts = Level_->CreateActor<GameEngineContentFont>(3);
	Fonts->SetPosition({ 50, 485 });
}

void BattleInterface::Render()
{
}

void BattleInterface::Update()
{
	//MoveKey();

	DoomChit();
	TimeCheck += (GameEngineTime::GetDeltaTime() * 2.0f);
	if (Level_->GetBattleState() != BattleState::BattlePage)
	{
		SelectOrder();
		OrderCheck();
	}

	if (PlayerStopCheck->GetPlayerStop() == true && OneTalk == false)
	{
		//김예나:플레이어 멈출시 폰트출력 테스트
		Fonts->ShowString("Wild Bulbarsaur\\is appear!!\\Go!!\\Charizard!!", false);
		OneTalk = true;
		//그 다음에 추가 폰트로 "가라 꼬부기!" 출력후 꼬부기 출현 + 배틀커맨드 이때 출현
	}

	{
		float Move = BattleUnitRenderer::PlayerRenderer_->GetPivot().x;
		//현재 플레이어 렌더 위치(x)를 가져옴

		// 폰트 출력이 완료되고 키입력 대기
		if (Fonts->IsWait())
		{
			// Z 키 입력시 다음 문장 출력
			if (GameEngineInput::GetInst()->IsDown("Z") == true)
			{
				// 다음 문장 출력 함수
				Fonts->NextString();
			}
		}
		// 다음 문장이 없을 때 == 끝났을 때
		if (Fonts->IsEnd())
		{
			PlayerEnd = true;
			// 모든 대화가 끝났을 때 z 키누르면 
			if (GameEngineInput::GetInst()->IsDown("Z") == true)
			{
				//애니메이션체인지
				BattleUnitRenderer::PlayerRenderer_->ChangeAnimation("Go");
				//이때 플레이어가 왼쪽으로 빠져야함

				if (BattleUnitRenderer::PlayerRenderer_->GetPivot().x < -960.0f)
				{
					BattleUnitRenderer::PlayerRenderer_->Off();
				}
			}
			// 모든 대화가 끝났을 때 x 키누르면 종료
			else if (GameEngineInput::GetInst()->IsDown("X") == true)
			{
				Fonts->EndFont();
			}
		}

		if (PlayerEnd == true)
		{
			BattleUnitRenderer::PlayerRenderer_->SetPivot({Move-(GameEngineTime::GetDeltaTime()*300.0f),31.0f});
			//플레이어 무빙 설정
		}
	}

}

bool BattleInterface::BattleKey()
{
	if (GameEngineInput::GetInst()->IsDown("SSelect"))
	{
		return true;
	}
	return false;
}

void BattleInterface::UsedSkillString(const std::string& _AttPokemon, const std::string& _AttSkill)
{
	DownFont_->EndFont();
	DownFont_->ShowString(_AttPokemon + " Used\\"+ _AttSkill + "!");
}

void BattleInterface::PoeFaintString(const std::string& _PoePokemon)
{
	DownFont_->EndFont();
	DownFont_->ShowString("Poe " + _PoePokemon + "\\fainted!");
}

void BattleInterface::SupperEffectString()
{
	DownFont_->EndFont();
	DownFont_->ShowString("It's Super effective!");
}

void BattleInterface::CriticalHitString()
{
	DownFont_->EndFont();
	DownFont_->ShowString("A critical hit!");
}

void BattleInterface::NotEffective()
{
	DownFont_->EndFont();
	DownFont_->ShowString("It's not Very effective;");
}

bool BattleInterface::MoveKey()
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



	// 장중혁 : Debug
	if (GameEngineInput::GetInst()->IsDown("SSelect"))
	{
		return true;
	}
	return false;
	//
}

void BattleInterface::DoomChit()
{
	if ((int)TimeCheck % 2 == 0)
	{
		MyHPUI->SetPivot({ 0.0f,-174.0f });
		MyHP->SetPivot({ 80.0f, -174.0f });
		EXP->SetPivot({ 48.0f,-174.0f });
	}

	if ((int)TimeCheck % 2 == 1)
	{
		MyHPUI->SetPivot({ 0.0f,-170.0f });
		MyHP->SetPivot({ 80.0f, -170.0f });
		EXP->SetPivot({ 48.0f,-170.0f });
	}
}

void BattleInterface::OrderCheck()
{
	switch (CurOrder)
	{
	case BattleOrder::Fight:
		BattleCommend->On();
		break;
	case BattleOrder::Pokemon:
		break;
	case BattleOrder::Bag:
		break;
	case BattleOrder::Run:
		break;
	default:
		break;
	}
}

void BattleInterface::SelectOrder()
{
	if ((GetSelect()->GetPivot().x == -190.0f && GetSelect()->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
	{	//싸우다 선택
		CurOrder = BattleOrder::Fight;
	}

	if ((GetSelect()->GetPivot().x == -190.0f && GetSelect()->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
	{	//포켓몬 선택
		CurOrder = BattleOrder::Pokemon;
	}

	if ((GetSelect()->GetPivot().x == 30.0f && GetSelect()->GetPivot().y == -25.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
	{	//가방 선택
		CurOrder = BattleOrder::Bag;
	}
	
	if ((GetSelect()->GetPivot().x == 30.0f && GetSelect()->GetPivot().y == 35.0f) && true == GameEngineInput::GetInst()->IsDown("SSelect"))
	{
		CurOrder = BattleOrder::Run;
	}

	if (CurOrder == BattleOrder::Fight && true == GameEngineInput::GetInst()->IsDown("SCancel"))
	{
		BattleCommend->Off();
		CurOrder = BattleOrder::None;
	}
}