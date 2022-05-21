#include "BattleEngine.h"
#include "BattleLevel.h"
#include "PokemonInfoManager.h"



BattleEngine::BattleEngine()
	: PlayerTurn_(false)
	, BattleLevel_(nullptr)
	, PlayerPokemon_(nullptr)
	, OpponentPokemon_(nullptr)
	, Random_(nullptr)
	, CurrentTurn_(BattleTurn::Off)
	, BattleStart_(false)
	, BattleFirstSupporter_(nullptr)
	, BattleSecondSupporter_(nullptr)
	, PlayerPokemonState_(nullptr)
	, OpponentPokemonState_(nullptr)
{
}

BattleEngine::~BattleEngine() 
{
	if (Random_ != nullptr)
	{
		delete Random_;
		Random_ = nullptr;
	}
}

void BattleEngine::Start()
{
	Random_ = new GameEngineRandom();
	// Opponent
}

void BattleEngine::Update()
{
	switch (CurrentTurn_)
	{
	case BattleTurn::Off:
		return;
		break;
	case BattleTurn::Wait:
		break;
	case BattleTurn::FirstTurn:
		break;
	case BattleTurn::SecondTurn:
		break;
	case BattleTurn::End:
		break;
	default:
		break;
	}
}

void BattleEngine::ScanBattleLevel()
{
	BattleLevel_ = dynamic_cast<BattleLevel*>(GetLevel());
	// BattleLevel에서 포켓몬을 가져온다
}

void BattleEngine::BattlePage(const std::string& _PlayerSkill, const std::string& _OpponentSkill)
{
	//InitialReSetting();
	{
		PokemonSkill* PlayerSkill = PokemonInfoManager::GetInst().FindSkill("_PlayerSkill");
		PokemonSkill* OpponentSkill = PokemonInfoManager::GetInst().FindSkill("_OpponentSkill");
		if (PlayerSkill == nullptr)
		{
			MsgBoxAssert("스킬 명이 다릅니다")
		}

		if (OpponentSkill == nullptr)
		{
			MsgBoxAssert("스킬 명이 다릅니다")
		}

		// CompareSpeed
		if (PlayerPokemon_->GetInfo()->GetSpeed() >= OpponentPokemon_->GetInfo()->GetSpeed())
		{
			PlayerTurn_ = true;
			BattleFirstSupporter_ = new BattlePageSupport(PlayerPokemonState_, OpponentPokemonState_, PlayerSkill);
			BattleSecondSupporter_ = new BattlePageSupport(OpponentPokemonState_, PlayerPokemonState_, OpponentSkill);
		}
		else
		{
			PlayerTurn_ = false;
			BattleFirstSupporter_ = new BattlePageSupport(OpponentPokemonState_, PlayerPokemonState_, OpponentSkill);
			BattleSecondSupporter_ = new BattlePageSupport(PlayerPokemonState_, OpponentPokemonState_, PlayerSkill);
		}
	}
	CurrentTurn_ = BattleTurn::FirstTurn;
}

PokemonBattleState* BattleEngine::CreatePokemon(Pokemon* _Pokemon)
{
	PokemonBattleState* NewPokemonState = new PokemonBattleState(_Pokemon);
	AllPokemonState_.push_back(NewPokemonState);
	return NewPokemonState;
}

void BattleEngine::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	PlayerPokemonState_ = CreatePokemon(PlayerPokemon_);
	OpponentPokemonState_ = CreatePokemon(OpponentPokemon_);
}

void BattleEngine::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (BattleFirstSupporter_ != nullptr)
	{
		delete BattleFirstSupporter_;
		BattleFirstSupporter_ = nullptr;
	}

	if (BattleSecondSupporter_ != nullptr)
	{
		delete BattleSecondSupporter_;
		BattleSecondSupporter_ = nullptr;
	}

	if (PlayerPokemonState_ != nullptr)
	{
		delete PlayerPokemonState_;
		PlayerPokemonState_ = nullptr;
	}

	if (OpponentPokemonState_ != nullptr)
	{
		delete OpponentPokemonState_;
		OpponentPokemonState_ = nullptr;
	}
	OpponentPokemon_ = nullptr;
	PlayerPokemon_ = nullptr;
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

bool PokemonBattleState::SetSkill(Pokemon* _AlppyPokemon, PokemonSkill* _Skill)
{
	// 면역일시 return false
	ApplySkill_[1][_AlppyPokemon].push_back(_Skill);
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
	default:
		break;

	}
	return 100.0f;
}

void PokemonBattleState::Update()
{
	for (auto& Skill : ApplySkill_)
	{
		if (Skill.first == 0)
		{
			// Skill.second.second->End()
		}
		else if (Skill.first <= -1)
		{
			// 무한 지속
		}
		else
		{

		}
	}
}

BattlePageSupport::BattlePageSupport(PokemonBattleState* _AttackPokemon, PokemonBattleState* _DefensePokemon, PokemonSkill* _Skill)
	: AttackPokemon_(_AttackPokemon)
	, DefensePokemon_(_DefensePokemon)
	, AttackPokemonSkill_(_Skill)
	, FinalValue_(0)
	, Random_(nullptr)
	, DamgeType_(TypeDamge::Error)
{
	Random_ = new GameEngineRandom();
}

BattlePageSupport::~BattlePageSupport()
{
	if (Random_ != nullptr)
	{
		delete Random_;
		Random_ = nullptr;
	}
}

TypeDamge BattlePageSupport::ComparePokemonType(const PokemonType& _Attack, const PokemonType& _Defend)
{
	switch (_Attack)
	{
	case PokemonType::NORMAL:
		switch (_Defend)
		{
		case PokemonType::ROCK:
			return TypeDamge::Bad;
			break;
		case PokemonType::GHOST:
			return TypeDamge::Nothing;
			break;
		default:
			break;
		}
		break;
	case PokemonType::FIRE:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return TypeDamge::Bad;
			break;
		case PokemonType::WATER:
			return TypeDamge::Bad;
			break;
		case PokemonType::GRASS:
			return TypeDamge::Great;
			break;
		case PokemonType::ICE:
			return TypeDamge::Great;
			break;
		case PokemonType::BUG:
			return TypeDamge::Great;
			break;
		case PokemonType::ROCK:
			return TypeDamge::Bad;
			break;
		case PokemonType::DRAGON:
			return TypeDamge::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::WATER:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return TypeDamge::Great;
			break;
		case PokemonType::WATER:
			return TypeDamge::Bad;
			break;
		case PokemonType::GRASS:
			return TypeDamge::Bad;
			break;
		case PokemonType::GROUND:
			return TypeDamge::Great;
			break;
		case PokemonType::ROCK:
			return TypeDamge::Great;
			break;
		case PokemonType::DRAGON:
			return TypeDamge::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::ELECTRIC:
		switch (_Defend)
		{
		case PokemonType::WATER:
			return TypeDamge::Great;
			break;
		case PokemonType::ELECTRIC:
			return TypeDamge::Bad;
			break;
		case PokemonType::GRASS:
			return TypeDamge::Bad;
			break;
		case PokemonType::GROUND:
			return TypeDamge::Nothing;
			break;
		case PokemonType::FLYING:
			return TypeDamge::Great;
			break;
		case PokemonType::DRAGON:
			return TypeDamge::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::GRASS:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return TypeDamge::Bad;
			break;
		case PokemonType::WATER:
			return TypeDamge::Great;
			break;
		case PokemonType::GRASS:
			return TypeDamge::Bad;
			break;
		case PokemonType::POISON:
			return TypeDamge::Bad;
			break;
		case PokemonType::GROUND:
			return TypeDamge::Great;
			break;
		case PokemonType::FLYING:
			return TypeDamge::Bad;
			break;
		case PokemonType::BUG:
			return TypeDamge::Bad;
			break;
		case PokemonType::ROCK:
			return TypeDamge::Great;
			break;
		case PokemonType::DRAGON:
			return TypeDamge::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::ICE:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return TypeDamge::Bad;
			break;
		case PokemonType::WATER:
			return TypeDamge::Bad;
			break;
		case PokemonType::GRASS:
			return TypeDamge::Great;
			break;
		case PokemonType::ICE:
			return TypeDamge::Bad;
			break;
		case PokemonType::GROUND:
			return TypeDamge::Great;
			break;
		case PokemonType::FLYING:
			return TypeDamge::Great;
			break;
		case PokemonType::DRAGON:
			return TypeDamge::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::FIGHTING:
		switch (_Defend)
		{
		case PokemonType::NORMAL:
			return TypeDamge::Great;
			break;
		case PokemonType::ICE:
			return TypeDamge::Great;
			break;
		case PokemonType::POISON:
			return TypeDamge::Bad;
			break;
		case PokemonType::FLYING:
			return TypeDamge::Bad;
			break;
		case PokemonType::PSYCHIC:
			return TypeDamge::Bad;
			break;
		case PokemonType::BUG:
			return TypeDamge::Bad;
			break;
		case PokemonType::ROCK:
			return TypeDamge::Great;
			break;
		case PokemonType::GHOST:
			return TypeDamge::Nothing;
			break;
		default:
			break;
		}
		break;
	case PokemonType::POISON:
		switch (_Defend)
		{
		case PokemonType::GRASS:
			return TypeDamge::Great;
			break;
		case PokemonType::POISON:
			return TypeDamge::Bad;
			break;
		case PokemonType::GROUND:
			return TypeDamge::Bad;
			break;
		case PokemonType::ROCK:
			return TypeDamge::Bad;
			break;
		case PokemonType::GHOST:
			return TypeDamge::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::GROUND:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return TypeDamge::Great;
			break;
		case PokemonType::ELECTRIC:
			return TypeDamge::Great;
			break;
		case PokemonType::GRASS:
			return TypeDamge::Bad;
			break;
		case PokemonType::POISON:
			return TypeDamge::Great;
			break;
		case PokemonType::FLYING:
			return TypeDamge::Nothing;
			break;
		case PokemonType::BUG:
			return TypeDamge::Bad;
			break;
		case PokemonType::ROCK:
			return TypeDamge::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::FLYING:
		switch (_Defend)
		{
		case PokemonType::ELECTRIC:
			return TypeDamge::Bad;
			break;
		case PokemonType::GRASS:
			return TypeDamge::Great;
			break;
		case PokemonType::FIGHTING:
			return TypeDamge::Great;
			break;
		case PokemonType::BUG:
			return TypeDamge::Great;
			break;
		case PokemonType::ROCK:
			return TypeDamge::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::PSYCHIC:
		switch (_Defend)
		{
		case PokemonType::FIGHTING:
			return TypeDamge::Great;
			break;
		case PokemonType::POISON:
			return TypeDamge::Great;
			break;
		case PokemonType::PSYCHIC:
			return TypeDamge::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::BUG:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return TypeDamge::Bad;
			break;
		case PokemonType::GRASS:
			return TypeDamge::Great;
			break;
		case PokemonType::FIGHTING:
			return TypeDamge::Bad;
			break;
		case PokemonType::POISON:
			return TypeDamge::Bad;
			break;
		case PokemonType::FLYING:
			return TypeDamge::Bad;
			break;
		case PokemonType::PSYCHIC:
			return TypeDamge::Great;
			break;
		case PokemonType::GHOST:
			return TypeDamge::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::ROCK:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return TypeDamge::Great;
			break;
		case PokemonType::ICE:
			return TypeDamge::Great;
			break;
		case PokemonType::FIGHTING:
			return TypeDamge::Bad;
			break;
		case PokemonType::GROUND:
			return TypeDamge::Bad;
			break;
		case PokemonType::FLYING:
			return TypeDamge::Great;
			break;
		case PokemonType::BUG:
			return TypeDamge::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::GHOST:
		switch (_Defend)
		{
		case PokemonType::NORMAL:
			return TypeDamge::Nothing;
			break;
		case PokemonType::PSYCHIC:
			return TypeDamge::Great;
			break;
		case PokemonType::GHOST:
			return TypeDamge::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::DRAGON:
		switch (_Defend)
		{
		case PokemonType::DRAGON:
			return TypeDamge::Great;
			break;
		default:
			break;
		}
		break;
	}
	return TypeDamge::Nomal;
}

void BattlePageSupport::UseSkillTurn()
{
	//PokemonInfo* AttackInfo;// = AttackPokemon_->GetInfo();
	//PokemonInfo* DefendInfo; //= DefensePokemon_->GetInfo();
	//switch (AttackPokemonSkill_->GetSkillType())
	//{
	//case SkillType::Physical:
	//{
	//	float CorrectionTypeValue = 1.0f;
	//	DamgeType_ = ComparePokemonType(AttackPokemonSkill_->GetType() , DefendInfo->GetMyType());
	//	switch (DamgeType_)
	//	{
	//	case TypeDamge::Great:
	//		CorrectionTypeValue = 2.0;
	//		break;
	//	case TypeDamge::Nomal:
	//		CorrectionTypeValue = 1.0;
	//		break;
	//	case TypeDamge::Bad:
	//		CorrectionTypeValue = 0.5;
	//		break;
	//	case TypeDamge::Nothing:
	//		CorrectionTypeValue = 0.0;
	//		break;
	//	default:
	//		break;
	//	}
	//	//int AttckValue = AttackInfo->GetAtt();
	//	//int AttckLevel = AttackInfo->GetMyLevel();
	//	//int DefendDef; //= DefendInfo->GetDef();
	//	//float SameType = AttackInfo->GetMyType() == _Skill->GetType() ? 1.5f : 1.0f;
	//	//int RandomValue = (Random_->RandomInt(217, 255)) * 100 / 255;
	//	//int FinalDamge = static_cast<int>((static_cast<float>(_Skill->GetValue() * AttckValue * (AttckLevel * 2 / 5 + 2)) * SameType) * CorrectionTypeValue) * RandomValue;
	//}
	//	break;
	//case SkillType::Special:

	//	break;
	//case SkillType::Status:

	//	break;
	//default:
	//	break;
	//}
}

void BattleEngine::InitialReSetting()
{
	PlayerTurn_ = true;
}

