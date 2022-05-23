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
	, PlayerCurrentPokemon_(nullptr)
	, PoeCurrentPokemon_(nullptr)
{

}

BattleLevel::~BattleLevel()
{
	BattleEngine::Destroy();
}

void BattleLevel::Loading()
{

	/// 장중혁 : BattleTestNPC1 DebugTest
	//Pokemon* Debug = CreateActor<Pokemon>();
	//Debug->SetInfo("Squirtle");
	//Opponent_ = CreateActor<BattleTestNPC1>();
	//Opponent_->PushPokemon(Debug);
	//PlayerCurrentPokemon_ = CreateActor<Pokemon>();
	//PlayerCurrentPokemon_->SetInfo("Charmander");
	//PoeCurrentPokemon_ = Opponent_->GetPokemon();
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

		}
		break;
	case BattleState::Battle:
		if (Interface_->BattleKey())
		{
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

}

void BattleLevel::FirstBattlePage()
{
}


void BattleLevel::SecondBattlePage()
{

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

BattleData::BattleData()
{
}

BattleData::~BattleData()
{
}

PokemonBattleState::PokemonBattleState(Pokemon* _Pokemon)
	: Pokemon_(_Pokemon)
	, CanAction_(true)
{
	{
		CurrentRank_[PokemonAbility::Att] = 0;
		CurrentRank_[PokemonAbility::Def] = 0;
		CurrentRank_[PokemonAbility::SpAtt] = 0;
		CurrentRank_[PokemonAbility::SpDef] = 0;
		CurrentRank_[PokemonAbility::Speed] = 0;
		CurrentRank_[PokemonAbility::Accuracy] = 0;
		CurrentRank_[PokemonAbility::Evasion] = 0;
	}
}

PokemonBattleState::~PokemonBattleState()
{
	for (auto* ApplySkill_ : AllCurrentApplySkill_)
	{
		if (ApplySkill_ != nullptr)
		{
			delete ApplySkill_;
		}
	}
}

bool PokemonBattleState::SetSkill(PokemonBattleState* _AlppyPokemon, PokemonSkill* _Skill)
{
	// 면역일시 return false
	ApplySkill* MakeApplySkill = new ApplySkill(_AlppyPokemon, _Skill);
	AllCurrentApplySkill_.push_back(MakeApplySkill);
	return true;
}

float PokemonBattleState::GetRank(const PokemonAbility& _State)
{
	switch (_State)
	{
	case PokemonAbility::Att:
	case PokemonAbility::Def:
	case PokemonAbility::SpAtt:
	case PokemonAbility::SpDef:
	case PokemonAbility::Speed:
		switch (CurrentRank_[_State])
		{
		case -6:
			return 0.25f;
			break;
		case -5:
			return 0.29f;
			break;
		case -4:
			return 0.33f;
			break;
		case -3:
			return 0.40f;
			break;
		case -2:
			return 0.50f;
			break;
		case -1:
			return 0.66f;
			break;
		case 0:
			return 0;
			break;
		case 1:
			return 1.5f;
			break;
		case 2:
			return 2.0f;
			break;
		case 3:
			return 2.5f;
			break;
		case 4:
			return 3.0f;
			break;
		case 5:
			return 3.5f;
			break;
		case 6:
			return 4.0f;
			break;
		default:
			MsgBoxAssert("랭크 수치가 잘못 되었습니다")
				break;
		}
		break;
	case PokemonAbility::Accuracy:
	case PokemonAbility::Evasion:
		switch (CurrentRank_[_State])
		{
		case -6:
			return 0.33f;
			break;
		case -5:
			return 0.38f;
			break;
		case -4:
			return 0.43f;
			break;
		case -3:
			return 0.50f;
			break;
		case -2:
			return 0.60f;
			break;
		case -1:
			return 0.75f;
			break;
		case 0:
			return 0;
			break;
		case 1:
			return 1.33f;
			break;
		case 2:
			return 1.66f;
			break;
		case 3:
			return 2.0f;
			break;
		case 4:
			return 2.33f;
			break;
		case 5:
			return 2.66f;
			break;
		case 6:
			return 3.0f;
			break;
		default:
			MsgBoxAssert("랭크 수치가 잘못 되었습니다")
				break;
		}
		break;
	default:
		break;

	}
	return 100.0f;
}

void PokemonBattleState::Update()
{
	for (auto* ApplySkill_ : AllCurrentApplySkill_)
	{
		int LeftTurn = (ApplySkill_)->GetLeftTurn();
		if (LeftTurn == 0)
		{
			// Skill.second.second->End()
		}
		else if (LeftTurn <= -1)
		{
			// 무한 지속
		}
		else
		{
			//(ApplySkill_)->Update();
			//(ApplySkill_)->TurnPass();
		}
	}
}