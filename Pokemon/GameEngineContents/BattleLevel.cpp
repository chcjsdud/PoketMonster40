#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

#include <GameEngineContentsCore/GameEngineContentFont.h>
#include "BattleTestNPC1.h"

#include "BattleLevel.h"
#include "BattleUnitRenderer.h"
#include "BattleBackground.h"
#include "BattleEngine.h"
#include "BattleNPCInterface.h"
#include "WildPokemonNPC.h"
#include "PokemonInfoManager.h"



BattleLevel::BattleLevel()
	: Interface_(nullptr)
	, BState_(BattleState::Openning)
	, OpenningEnd_(false)
	, EnddingEnd_(false)
	// 디버깅
	, PlayerCurrentPokemon_(nullptr)
	, PoeCurrentPokemon_(nullptr)
	, PlayerRed_(nullptr)
	, Opponent_(nullptr)
	, PlayerStopCheck(nullptr)
	, OneTalk(false)
	, Fonts(nullptr)
	, BattleData_(nullptr)
{

}

BattleLevel::~BattleLevel()
{	
	if (BattleData_ != nullptr)
	{
		{
			delete BattleData_;
		}
	}
	if (Opponent_ != nullptr)
	{
		delete Opponent_->GetPokemonList()[0];
		delete PlayerRed_->GetPokemonList().front();
	}
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
	//PoeCurrentPokemon_ = Opponent_->GetPokemonList();
	// Debug



	CreateActor<BattleBackground>();

	Interface_ = CreateActor<BattleInterface>(3);
	Interface_->SetPosition({ 720.0f, 548.0f });

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
} 

void BattleLevel::LevelChangeStart(GameEngineLevel * _PrevLevel)
{

	if (PlayerRed_ == nullptr)
	{
		PlayerRed_  = PlayerRed::MainRed_;
	}

	//BState_ = BattleState::Openning
	{
		BState_ = BattleState::Selecet;
		OpenningEnd_ = false;
		EnddingEnd_ = false;
		ShowOpenning();
	}



	// 장중혁 : 배틀 디버깅
	{
		Opponent_ = CreateActor<BattleNPCInterface>(0, "Debug");
		Opponent_->PushPokemon(PokemonInfoManager::GetInst().CreatePokemon("Charmander"));
		PlayerRed_->GetPokemonList().push_back(PokemonInfoManager::GetInst().CreatePokemon("Squirtle"));

		BattleData_ = new BattleData(PlayerRed_, Opponent_, this);
	}
}

void BattleLevel::ShowOpenning()
{

}


void BattleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	OpenningEnd_ = false;
	EnddingEnd_ = false;

	// 장중혁 : Debug
	{
		Opponent_->Death();
		Opponent_->GetPokemonList()[0]->Death();
		PlayerRed_->GetPokemonList().front()->Death();
		delete BattleData_;
	}
}

void BattleLevel::ShowEndding()
{
}


BattleData::BattleData(PlayerRed* _Player, BattleNPCInterface* _Poe, BattleLevel* _Level)
	: PlayerCurrentPokemonInBattle_(nullptr)
	, PoeCurrentPokemonInBattle_(nullptr)
	, PoeNPC_(_Poe)
	, Player_(_Player)
	, PlayerPokemonList_(_Player->GetPokemonList())
	, PoePokemonList_(_Poe->GetPokemonList())
	, WildBattle_(false)
{
	{
		// Player
		size_t PokemonInt = PlayerPokemonList_.size();
		for (size_t i = 0; i < PokemonInt; i++)
		{
			PlayerPokemonsInBattle_.push_back(CreatePokemonState(PlayerPokemonList_[i]));
		}
	}
	{
		// Poe
		size_t PokemonInt = PoePokemonList_.size();
		for (size_t i = 0; i < PokemonInt; i++)
		{
			PeoPokemonsInBattle_.push_back(CreatePokemonState(PoePokemonList_[i]));
		}
	}

	PlayerCurrentPokemonInBattle_ = PlayerPokemonsInBattle_.front();
	PoeCurrentPokemonInBattle_ = PeoPokemonsInBattle_.front();
}

BattleData::BattleData(PlayerRed* _Player, Pokemon* _WildPokemon, BattleLevel* _Level)
	: PlayerCurrentPokemonInBattle_(nullptr)
	, PoeCurrentPokemonInBattle_(nullptr)
	, PoeNPC_(nullptr)
	, Player_(_Player)
	, PlayerPokemonList_(_Player->GetPokemonList())
	, PoePokemonList_(_Level->CreateActor<WildPokemonNPC>(0, "WildPokemon")->GetPokemonList())
	, WildBattle_(true)
{
	// PlayerCurrentPokemonInBattle_ = _Player->GetPlayerPokemon
	PoeNPC_ = dynamic_cast<BattleNPCInterface*>(_Level->FindActor("WildPokemon"));
	
	{
		// Player
		size_t PokemonInt = PlayerPokemonList_.size();
		for (size_t i = 0; i < PokemonInt; i++)
		{
			PlayerPokemonsInBattle_.push_back(CreatePokemonState(PlayerPokemonList_[i]));
		}
	}

	{
		// Poe
		size_t PokemonInt = PoePokemonList_.size();
		for (size_t i = 0; i < PokemonInt; i++)
		{
			PeoPokemonsInBattle_.push_back(CreatePokemonState(PoePokemonList_[i]));
		}
	}

	PlayerCurrentPokemonInBattle_ = PlayerPokemonsInBattle_.front();
	PoeCurrentPokemonInBattle_ = PeoPokemonsInBattle_.front();
}

BattleData::~BattleData()
{
	if (WildBattle_ == true)
	{
		PoeNPC_->Death();
	}

	for (auto* State : AllPokemonInBattle_)
	{
		if (State != nullptr)
		{
			delete State;
			State = nullptr;
		}
	}
}

PokemonBattleState* BattleData::CreatePokemonState(Pokemon* _Pokemon)
{
	PokemonBattleState* PokemonState = new PokemonBattleState(_Pokemon);
	AllPokemonInBattle_.push_back(PokemonState);
	return PokemonState;
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