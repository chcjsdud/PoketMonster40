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
	, BattleManager_(nullptr)
{

}

BattleLevel::~BattleLevel()
{	
	if (BattleData_ != nullptr)
	{
		delete BattleData_;
		BattleData_ = nullptr;
	}
	if (Opponent_ != nullptr)
	{
		delete Opponent_->GetPokemonList()[0];
		delete PlayerRed_->GetPokemonList().front();
		PlayerRed_ = nullptr;
		Opponent_ = nullptr;
	}

	if (BattleManager_ != nullptr)
	{
		delete BattleManager_;
		BattleManager_ = nullptr;
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
	int a = 0;
	switch (BState_)
	{
	case BattleState::Openning:
		if (OpenningEnd_ == true)
		{
			BState_ = BattleState::SelecetPage;
		}
		return;
		break;
	case BattleState::SelecetPage:
		if (Interface_->MoveKey() == true)
		{
			StartBattlePage("Tackle", "Scratch");
		}
		break;
	case BattleState::BattlePage:
		if (Interface_->BattleKey())
		{
			if (BattleManager_->Update() == true)
			{
				EndBattlePage();
			}

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

void BattleLevel::StartBattlePage(const std::string& _PlayerSkill, const std::string& _PoeSkill)
{
	RefreshPokemon();
	{
		std::string Player = GameEngineString::ToUpperReturn(_PlayerSkill);
		std::string Poe = GameEngineString::ToUpperReturn(_PoeSkill);
		bool Bool = false;
		std::vector<PokemonSkillInfo*>& PlayerSkill = PlayerCurrentPokemon_->GetPokemon()->GetInfo()->GetSkill();
		std::vector<PokemonSkillInfo*>& PoeSkill = PoeCurrentPokemon_->GetPokemon()->GetInfo()->GetSkill();
		for (auto& Skill : PlayerSkill)
		{
			if (Skill == nullptr)
			{
				continue;
			}
			if (Skill->GetNameConstRef() == Player)
			{
				Bool = true;
				break;
			}
		}

		for (auto& Skill : PoeSkill)
		{
			if (Skill == nullptr)
			{
				continue;
			}
			if (Skill->GetNameConstRef() == Poe)
			{
				Bool = true;
				break;
			}
		}

		if (Bool == false)
		{
			MsgBoxAssert("해당 포켓몬은 스킬을 가지고 있지 않습니다");
		}
	}

	BattleManager_ = new BattleManager(_PlayerSkill, _PoeSkill, this);
	BState_ = BattleState::BattlePage;
	BattleManager_->Update();
}

void BattleLevel::EndBattlePage()
{
	if (BattleManager_ != nullptr)
	{
		delete BattleManager_;
		BattleManager_ = nullptr;
	}
	BState_ = BattleState::SelecetPage;

}

void BattleLevel::LevelChangeStart(GameEngineLevel * _PrevLevel)
{

	if (PlayerRed_ == nullptr)
	{
		PlayerRed_  = PlayerRed::MainRed_;
	}

	//BState_ = BattleState::Openning
	{
		BState_ = BattleState::SelecetPage;
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
		RefreshPokemon();
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
		for (auto& Iter : PlayerRed_->GetPokemonList())
		{
			delete Iter;
		}
			PlayerRed_->GetPokemonList().clear();
		for (auto& Iter : Opponent_->GetPokemonList())
		{
			delete Iter;
		}
			Opponent_->GetPokemonList().clear();

		Opponent_->Death();
		delete BattleData_;
		BattleData_ = nullptr;
	}
}

void BattleLevel::ShowEndding()
{
}

void BattleLevel::RefreshPokemon()
{
	if (BattleData_ != nullptr)
	{
		PlayerCurrentPokemon_ = BattleData_->GetCurrentPlayerPokemon();
		PoeCurrentPokemon_ = BattleData_->GetCurrentPoePokemon();
	}

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

bool PokemonBattleState::SetSkill(PokemonBattleState* _AlppyPokemon, PokemonSkillInfo* _Skill)
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
			return 1;
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
			return 1;
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

BattleManager::BattleManager(const std::string& _PlayerSkill, const std::string& _PoeSkill, BattleLevel* _Level)
	: PlayerSkill_(PokemonInfoManager::GetInst().FindSkillInfo(_PlayerSkill))
	, PoeSkill_(PokemonInfoManager::GetInst().FindSkillInfo(_PoeSkill))
	, PlayCurrentPokemon_(_Level->BattleData_->GetCurrentPlayerPokemon())
	, PoeCurrentPokemon_(_Level->BattleData_->GetCurrentPoePokemon())
	, Select_(BattleOrderMenu::Fight)
	, CurrentBattlePage_(BattlePage::FirstBattle)
	, PlayerFirst_(false)
	, Interface_(_Level->Interface_)
	, CurrentFont_(Battlefont::None)
	, FristTurn_(nullptr)
	, SecondTurn_(nullptr)
{
	if (PlayerSkill_ == nullptr || PoeSkill_ == nullptr)
	{
		MsgBoxAssert("스킬명이 일치하지 않습니다")
	}

	switch (Select_)
	{
	case BattleOrderMenu::Run:
	case BattleOrderMenu::Fight:
		PlayerFirst_ = BattleEngine::ComareSpeed(PlayCurrentPokemon_, PoeCurrentPokemon_);
		break;
	case BattleOrderMenu::Item:
		break;
	case BattleOrderMenu::Pokemon:
		break;

	default:
		break;
	}
	

}

bool BattleManager::Update()
{
	PokemonBattleState* CurrentTurn = nullptr;
	PokemonSkillInfo* CurrentPokemonSkill = nullptr;

	PokemonBattleState* AfterTrun = nullptr;
	PokemonSkillInfo* AfterPokemonSkill = nullptr;
	if (PlayerFirst_ == true)
	{
		CurrentTurn = PlayCurrentPokemon_;
		CurrentPokemonSkill = PlayerSkill_;
		AfterTrun = PoeCurrentPokemon_;
		AfterPokemonSkill = PoeSkill_;
	}
	else
	{
		CurrentTurn = PoeCurrentPokemon_;
		CurrentPokemonSkill = PoeSkill_;
		AfterTrun = PlayCurrentPokemon_;
		AfterPokemonSkill = PlayerSkill_;
	}
	switch (CurrentBattlePage_)
	{
	case BattlePage::FirstBattle:
		switch (Select_)
		{
		case BattleOrderMenu::Fight:
			if (FristTurn_ == nullptr)
			{
				FristTurn_ = new BattleTurn(CurrentTurn, AfterTrun, CurrentPokemonSkill->GetSkillType());
			}
			if (CheckFont(CurrentTurn, AfterTrun, CurrentPokemonSkill, FristTurn_))
			{
				delete FristTurn_;
				FristTurn_ = nullptr;
				CurrentBattlePage_ = BattlePage::SecondBattle;
			}
			break;
		case BattleOrderMenu::Item:
			break;
		case BattleOrderMenu::Pokemon:
			break;
		case BattleOrderMenu::Run:
			break;
		default:
			break;
		}
		break;
	case BattlePage::SecondBattle:
		switch (Select_)
		{
		case BattleOrderMenu::Fight:
			if (SecondTurn_ == nullptr)
			{
				SecondTurn_ = new BattleTurn(CurrentTurn, AfterTrun, CurrentPokemonSkill->GetSkillType());
			}
			if (CheckFont(CurrentTurn, AfterTrun, CurrentPokemonSkill, SecondTurn_))
			{
				delete SecondTurn_;
				SecondTurn_ = nullptr;
				CurrentBattlePage_ = BattlePage::End;
			}
			break;
		case BattleOrderMenu::Item:
			break;
		case BattleOrderMenu::Pokemon:
			break;
		case BattleOrderMenu::Run:
			break;
		default:
			break;
		}
		break;
	case BattlePage::End:
		return true;
		break;
	}
	return false;
}

bool BattleManager::CheckFont(PokemonBattleState* _CurrentTurn, PokemonBattleState* _AfterTrun, PokemonSkillInfo* _Skill, BattleTurn* _Turn)
{

	switch (CurrentFont_)
	{
	case Battlefont::None:
		Interface_->ShowUsedSkillString(_CurrentTurn->GetPokemon()->GetInfo()->GetNameConstRef(), _Skill->GetNameConstRef());
		_Turn->DamageType_ = BattleEngine::ComparePokemonType(_Skill, _AfterTrun);
		_Turn->FinalDamage_ = BattleEngine::AttackCalculation(_CurrentTurn, _AfterTrun, _Skill, _Turn->DamageType_);
		CurrentFont_ = Battlefont::Wait;
		break;

	case Battlefont::Att:
		// 어택 모션
		break;
	case Battlefont::Wait:
		if (_Turn->Critical_ == true)
		{
			Interface_->ShowCriticalHitString();
			FristTurn_->Critical_ = false;
		}
		else
		{
			switch (_Turn->DamageType_)
			{
			case DamageType::Great:
				Interface_->ShowSupperEffectString();
				break;
			case DamageType::Bad:
				Interface_->ShowNotEffective();
				break;
			case DamageType::Nothing:
				Interface_->ShowFailed();
				break;
			default:
				break;
			}
			CurrentFont_ = Battlefont::None;
			PlayerFirst_ = !PlayerFirst_;
			return true;
		}
		//효과는 대단했다
		break; 
	case Battlefont::Effect:
		break;
	default:
		break;
	}
	return false;
}

BattleManager::BattleTurn::BattleTurn(PokemonBattleState* const _Att, PokemonBattleState* const _Def, SkillType _Skill)
	: AttPokemon_(_Att)
	, DefPokemon_(_Def)
	, FinalDamage_(0)
	, Critical_(false)
	, DamageType_(DamageType::Nomal)
	, SkillType_(_Skill)
{

}