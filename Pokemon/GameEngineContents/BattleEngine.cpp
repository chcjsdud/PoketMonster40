#include "BattleEngine.h"
#include <GameEngineBase/GameEngineDebug.h>


BattleEngine::BattleEngine()
{

}

BattleEngine::~BattleEngine()
{

}

// true 시 주인공 선공
bool BattleEngine::ComareSpeed(PokemonBattleState* _Player, PokemonBattleState* _Poe)
{
	int PlayerSpeed = static_cast<int>(_Player->GetPokemon()->GetInfo()->GetSpeed() * _Player->GetRank(PokemonAbility::Speed));

	int PoeSpeed = static_cast<int>(_Poe->GetPokemon()->GetInfo()->GetSpeed() * _Poe->GetRank(PokemonAbility::Speed));

	return PlayerSpeed >= PoeSpeed ? true : false;
}

float BattleEngine::AttackCalculation(const PokemonBattleState* _Att, const PokemonBattleState* _Def, PokemonSkill* _Skill, const DamgeType& _DamgeType)
{
	//_Att->Pokemon_->GetInfo()->GetSkill();
	PokemonInfo* AttPlayerInfo = _Att->Pokemon_->GetInfo();
	PokemonInfo* DefPlayerInfo = _Def->Pokemon_->GetInfo();
	SkillType SkillType = _Skill->GetSkillType();

	int AttLevel = _Att->Pokemon_->GetInfo()->GetMyLevel();
	int SkillPower = _Skill->GetValue();

	int AttPower = SkillType == SkillType::Physical ? AttPlayerInfo->GetAtt() * const_cast<PokemonBattleState*>(_Att)->GetRank(PokemonAbility::Att) 
		: AttPlayerInfo->GetSpAtt() * const_cast<PokemonBattleState*>(_Att)->GetRank(PokemonAbility::SpAtt);

	int DefDefence = SkillType == SkillType::Physical ? DefPlayerInfo->GetDef() * const_cast<PokemonBattleState*>(_Def)->GetRank(PokemonAbility::Def)
		: DefPlayerInfo->GetSpDef() * const_cast<PokemonBattleState*>(_Def)->GetRank(PokemonAbility::SpDef);

	float Mod1 = 1.0;
	{
		for (auto& ApplySkill : _Att->AllCurrentApplySkill_)
		{
			
		}
	}

	float Critical = 1.0f;
	int RandomValue = (GameEngineRandom::GetInst_->RandomInt(217, 255) * 100) / 255;
	float SameType = _Att->Pokemon_->GetInfo()->GetMyType() == _Skill->GetType() ? 1.5f : 1.0f;
	float CompareType = 1.0f;
	switch (_DamgeType)
	{
	case DamgeType::Great:
		CompareType = 2.0f;
		break;
	case DamgeType::Nomal:
		CompareType = 1.0f;
		break;
	case DamgeType::Bad:
		CompareType = 0.5f;
		break;
	case DamgeType::Nothing:
		CompareType = 0.0f;
		break;
	default:
		break;
	}
	//float FinalDamage = (((( AttLevel * 2 / 5 ) + 2 ) * SkillPower * AttPower / 50 ) / DefDefence ) *
	
	
	return 1.0f;
}

DamgeType BattleEngine::ComparePokemonType(const PokemonType& _Attack, const PokemonType& _Defend)
{
	switch (_Attack)
	{
	case PokemonType::NORMAL:
		switch (_Defend)
		{
		case PokemonType::ROCK:
			return DamgeType::Bad;
			break;
		case PokemonType::GHOST:
			return DamgeType::Nothing;
			break;
		default:
			break;
		}
		break;
	case PokemonType::FIRE:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return DamgeType::Bad;
			break;
		case PokemonType::WATER:
			return DamgeType::Bad;
			break;
		case PokemonType::GRASS:
			return DamgeType::Great;
			break;
		case PokemonType::ICE:
			return DamgeType::Great;
			break;
		case PokemonType::BUG:
			return DamgeType::Great;
			break;
		case PokemonType::ROCK:
			return DamgeType::Bad;
			break;
		case PokemonType::DRAGON:
			return DamgeType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::WATER:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return DamgeType::Great;
			break;
		case PokemonType::WATER:
			return DamgeType::Bad;
			break;
		case PokemonType::GRASS:
			return DamgeType::Bad;
			break;
		case PokemonType::GROUND:
			return DamgeType::Great;
			break;
		case PokemonType::ROCK:
			return DamgeType::Great;
			break;
		case PokemonType::DRAGON:
			return DamgeType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::ELECTRIC:
		switch (_Defend)
		{
		case PokemonType::WATER:
			return DamgeType::Great;
			break;
		case PokemonType::ELECTRIC:
			return DamgeType::Bad;
			break;
		case PokemonType::GRASS:
			return DamgeType::Bad;
			break;
		case PokemonType::GROUND:
			return DamgeType::Nothing;
			break;
		case PokemonType::FLYING:
			return DamgeType::Great;
			break;
		case PokemonType::DRAGON:
			return DamgeType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::GRASS:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return DamgeType::Bad;
			break;
		case PokemonType::WATER:
			return DamgeType::Great;
			break;
		case PokemonType::GRASS:
			return DamgeType::Bad;
			break;
		case PokemonType::POISON:
			return DamgeType::Bad;
			break;
		case PokemonType::GROUND:
			return DamgeType::Great;
			break;
		case PokemonType::FLYING:
			return DamgeType::Bad;
			break;
		case PokemonType::BUG:
			return DamgeType::Bad;
			break;
		case PokemonType::ROCK:
			return DamgeType::Great;
			break;
		case PokemonType::DRAGON:
			return DamgeType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::ICE:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return DamgeType::Bad;
			break;
		case PokemonType::WATER:
			return DamgeType::Bad;
			break;
		case PokemonType::GRASS:
			return DamgeType::Great;
			break;
		case PokemonType::ICE:
			return DamgeType::Bad;
			break;
		case PokemonType::GROUND:
			return DamgeType::Great;
			break;
		case PokemonType::FLYING:
			return DamgeType::Great;
			break;
		case PokemonType::DRAGON:
			return DamgeType::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::FIGHTING:
		switch (_Defend)
		{
		case PokemonType::NORMAL:
			return DamgeType::Great;
			break;
		case PokemonType::ICE:
			return DamgeType::Great;
			break;
		case PokemonType::POISON:
			return DamgeType::Bad;
			break;
		case PokemonType::FLYING:
			return DamgeType::Bad;
			break;
		case PokemonType::PSYCHIC:
			return DamgeType::Bad;
			break;
		case PokemonType::BUG:
			return DamgeType::Bad;
			break;
		case PokemonType::ROCK:
			return DamgeType::Great;
			break;
		case PokemonType::GHOST:
			return DamgeType::Nothing;
			break;
		default:
			break;
		}
		break;
	case PokemonType::POISON:
		switch (_Defend)
		{
		case PokemonType::GRASS:
			return DamgeType::Great;
			break;
		case PokemonType::POISON:
			return DamgeType::Bad;
			break;
		case PokemonType::GROUND:
			return DamgeType::Bad;
			break;
		case PokemonType::ROCK:
			return DamgeType::Bad;
			break;
		case PokemonType::GHOST:
			return DamgeType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::GROUND:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return DamgeType::Great;
			break;
		case PokemonType::ELECTRIC:
			return DamgeType::Great;
			break;
		case PokemonType::GRASS:
			return DamgeType::Bad;
			break;
		case PokemonType::POISON:
			return DamgeType::Great;
			break;
		case PokemonType::FLYING:
			return DamgeType::Nothing;
			break;
		case PokemonType::BUG:
			return DamgeType::Bad;
			break;
		case PokemonType::ROCK:
			return DamgeType::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::FLYING:
		switch (_Defend)
		{
		case PokemonType::ELECTRIC:
			return DamgeType::Bad;
			break;
		case PokemonType::GRASS:
			return DamgeType::Great;
			break;
		case PokemonType::FIGHTING:
			return DamgeType::Great;
			break;
		case PokemonType::BUG:
			return DamgeType::Great;
			break;
		case PokemonType::ROCK:
			return DamgeType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::PSYCHIC:
		switch (_Defend)
		{
		case PokemonType::FIGHTING:
			return DamgeType::Great;
			break;
		case PokemonType::POISON:
			return DamgeType::Great;
			break;
		case PokemonType::PSYCHIC:
			return DamgeType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::BUG:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return DamgeType::Bad;
			break;
		case PokemonType::GRASS:
			return DamgeType::Great;
			break;
		case PokemonType::FIGHTING:
			return DamgeType::Bad;
			break;
		case PokemonType::POISON:
			return DamgeType::Bad;
			break;
		case PokemonType::FLYING:
			return DamgeType::Bad;
			break;
		case PokemonType::PSYCHIC:
			return DamgeType::Great;
			break;
		case PokemonType::GHOST:
			return DamgeType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::ROCK:
		switch (_Defend)
		{
		case PokemonType::FIRE:
			return DamgeType::Great;
			break;
		case PokemonType::ICE:
			return DamgeType::Great;
			break;
		case PokemonType::FIGHTING:
			return DamgeType::Bad;
			break;
		case PokemonType::GROUND:
			return DamgeType::Bad;
			break;
		case PokemonType::FLYING:
			return DamgeType::Great;
			break;
		case PokemonType::BUG:
			return DamgeType::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::GHOST:
		switch (_Defend)
		{
		case PokemonType::NORMAL:
			return DamgeType::Nothing;
			break;
		case PokemonType::PSYCHIC:
			return DamgeType::Great;
			break;
		case PokemonType::GHOST:
			return DamgeType::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::DRAGON:
		switch (_Defend)
		{
		case PokemonType::DRAGON:
			return DamgeType::Great;
			break;
		default:
			break;
		}
		break;
	}
	return DamgeType::Nomal;
}