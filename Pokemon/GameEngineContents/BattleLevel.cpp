#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

#include <GameEngineContentsCore/GameEngineContentFont.h>
#include "BattleTestNPC1.h"

#include "BattleLevel.h"
#include "BattleUnitRenderer.h"
#include "BattleBackground.h"
#include "BattleEngine.h"



BattleLevel::BattleLevel()
	: Interface_(nullptr)
	, BState_(BattleState::Openning)
	, OpenningEnd_(false)
	, EnddingEnd_(false)
	, PlayerRed_(nullptr)
	, OneTalk(false)
	, Fonts(nullptr)
	// 디버깅
	, Opponent_(nullptr)
	, PlayerPokemon_(nullptr)
	, OpponentPokemon_(nullptr)
	, InBattle_(BattleTurn::Off)
{

}

BattleLevel::~BattleLevel()
{
	BattleEngine::Destroy();
}

void BattleLevel::Loading()
{

	/// 장중혁 : BattleTestNPC1 DebugTest
	Pokemon* Debug = CreateActor<Pokemon>();
	Debug->SetInfo("Squirtle");
	Opponent_ = CreateActor<BattleTestNPC1>();
	Opponent_->PushPokemon(Debug);
	PlayerPokemon_ = CreateActor<Pokemon>();
	PlayerPokemon_->SetInfo("Charmander");
	OpponentPokemon_ = Opponent_->GetPokemon();
	// Debug



	CreateActor<BattleBackground>();

	Interface_ = CreateActor<BattleInterface>(3);
	Interface_->SetPosition({ 720.0f, 548.0f });
	
	//김예나:테스트 코드
	PlayerStopCheck = CreateActor<BattleUnitRenderer>();
	Fonts = CreateActor<GameEngineContentFont>(3);
	Fonts->SetPosition({ 50, 485 });


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
		if (Interface_->MoveKey() == true)
		{
			// 메뉴 확인 로직 필요
			// 장중혁 : debug
			InBattle_ = BattleTurn::FirstTurn;
			BattlePageStart();
		}
		break;
	case BattleState::Battle:
		if (Interface_->BattleKey())
		{
			NextStringTrun();
		}
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

	//

	if (PlayerStopCheck->GetPlayerStop()==true&&OneTalk==false)
	{
		//김예나:플레이어 멈출시 폰트출력 테스트
		Fonts->ShowString("Wild Bulbarsaur\\is appear!!", false);
		OneTalk = true;
		//그 다음에 추가 폰트로 "가라 꼬부기!" 출력후 꼬부기 출현 + 배틀커맨드 이때 출현
	}
} 

void BattleLevel::NextStringTrun()
{

}

void BattleLevel::BattlePageStart()
{
	switch (InBattle_)
	{
	case BattleTurn::Off:
		break;
	case BattleTurn::FirstTurn:
		FirstBattlePage();
		break;
	case BattleTurn::SecondTurn:
		SecondBattlePage();
		break;
	case BattleTurn::BattleEnd:
		break;
	default:
		break;
	}
}

void BattleLevel::FirstBattlePage()
{
	bool IsPlayerTurn = BattleEngine::GetInst()->StartBattlePage("Scratch", "Tackle");// Debug
	BState_ = BattleState::Battle; // Debug
	InBattle_ = BattleTurn::FirstTurn;
	if (IsPlayerTurn)
	{
		//Interface_->UsedSkillString(PlayerPokemon_->GetNameConstRef() , OpponentPokemon_->GetNameConstRef(), "Scratch");
	}
	else
	{
		//Interface_->UsedSkillString(OpponentPokemon_->GetNameConstRef(), PlayerPokemon_->GetNameConstRef(), "Scratch");
	}
	// 포켓몬 배정되면 인터페이스와 엔진에 구현하는 기능 추가 해야함 <-
}


void BattleLevel::SecondBattlePage()
{

}


void BattleLevel::LevelChangeStart(GameEngineLevel * _PrevLevel)
{
	// 장중혁 : Debug
	BattleEngine::GetInst()->BattleStart(PlayerPokemon_, OpponentPokemon_); // Debug
	//

	if (PlayerRed_ == nullptr)
	{
		PlayerRed_  = PlayerRed::MainRed_;
	}



	//BState_ = BattleState::Openning
	BState_ = BattleState::Selecet;
	OpenningEnd_ = false;
	EnddingEnd_ = false;
	InBattle_ = BattleTurn::Off;
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