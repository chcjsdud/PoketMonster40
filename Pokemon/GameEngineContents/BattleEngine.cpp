#include "BattleEngine.h"
#include <cmath>
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

int BattleEngine::AttackCalculation(const PokemonBattleState* _Att, const PokemonBattleState* _Def, PokemonSkillInfo* _Skill, const DamageType& _DamageType)
{
	//_Att->Pokemon_->GetInfo()->GetSkill();
	PokemonInfo* AttPlayerInfo = _Att->Pokemon_->GetInfo();
	PokemonInfo* DefPlayerInfo = _Def->Pokemon_->GetInfo();
	SkillType SkillType = _Skill->GetSkillType();

	int AttLevel = _Att->Pokemon_->GetInfo()->GetMyLevel();
	float SkillPower = static_cast<float>(_Skill->GetValue());

	float AttPower = SkillType == SkillType::Physical ? static_cast<float>(AttPlayerInfo->GetAtt()) * const_cast<PokemonBattleState*>(_Att)->GetRank(PokemonAbility::Att)
		: static_cast<float>(AttPlayerInfo->GetSpAtt()) * const_cast<PokemonBattleState*>(_Att)->GetRank(PokemonAbility::SpAtt);

	float DefDefence = SkillType == SkillType::Physical ? static_cast<float>(DefPlayerInfo->GetDef()) * const_cast<PokemonBattleState*>(_Def)->GetRank(PokemonAbility::Def)
		: static_cast<float>(DefPlayerInfo->GetSpDef()) * const_cast<PokemonBattleState*>(_Def)->GetRank(PokemonAbility::SpDef);

	float Mod1 = 1.0f;
	{
		for (auto& ApplyStatus : _Att->ApplyStatus_)
		{
			if (ApplyStatus == StatusEffect::BRN)
			{
				Mod1 *= 0.5f;
			}
		}
	}

	float Critical = 1.0f;
	int RandomValue = (GameEngineRandom::GetInst_->RandomInt(217, 255) * 100) / 255;
	float SameType = _Att->Pokemon_->GetInfo()->GetMyType() == _Skill->GetType() ? 1.5f : 1.0f;
	float CompareType = 1.0f;

	{
	switch (_DamageType)
	{
		case DamageType::Great:
			CompareType = 2.0f;
			break;
		case DamageType::Nomal:
			CompareType = 1.0f;
			break;
		case DamageType::Bad:
			CompareType = 0.5f;
			break;
		case DamageType::Nothing:
			CompareType = 0.0f;
			break;
		default:
			break;
		}
	}

	int FinalDamage = (static_cast<int>(floor(floor(floor((floor(floor(static_cast<float>(static_cast<int>((static_cast<float>(( AttLevel * 2 / 5 ) + 2 ) * SkillPower) * AttPower) / 50 ) / DefDefence ) * Mod1 ) + 2.0f ) * Critical )
	* SameType) * CompareType) * RandomValue) / 100);
	
	
	return FinalDamage;
}

DamageType BattleEngine::ComparePokemonType(const PokemonSkillInfo* _Attack, const PokemonBattleState* _Defend)
{
	PokemonType Attack = const_cast<PokemonSkillInfo*>(_Attack)->GetType();
	PokemonType Defend = _Defend->Pokemon_->GetInfo()->GetMyType();

	switch (Attack)
	{
	case PokemonType::NORMAL:
		switch (Defend)
		{
		case PokemonType::ROCK:
			return DamageType::Bad;
			break;
		case PokemonType::GHOST:
			return DamageType::Nothing;
			break;
		default:
			break;
		}
		break;
	case PokemonType::FIRE:
		switch (Defend)
		{
		case PokemonType::FIRE:
			return DamageType::Bad;
			break;
		case PokemonType::WATER:
			return DamageType::Bad;
			break;
		case PokemonType::GRASS:
			return DamageType::Great;
			break;
		case PokemonType::ICE:
			return DamageType::Great;
			break;
		case PokemonType::BUG:
			return DamageType::Great;
			break;
		case PokemonType::ROCK:
			return DamageType::Bad;
			break;
		case PokemonType::DRAGON:
			return DamageType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::WATER:
		switch (Defend)
		{
		case PokemonType::FIRE:
			return DamageType::Great;
			break;
		case PokemonType::WATER:
			return DamageType::Bad;
			break;
		case PokemonType::GRASS:
			return DamageType::Bad;
			break;
		case PokemonType::GROUND:
			return DamageType::Great;
			break;
		case PokemonType::ROCK:
			return DamageType::Great;
			break;
		case PokemonType::DRAGON:
			return DamageType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::ELECTRIC:
		switch (Defend)
		{
		case PokemonType::WATER:
			return DamageType::Great;
			break;
		case PokemonType::ELECTRIC:
			return DamageType::Bad;
			break;
		case PokemonType::GRASS:
			return DamageType::Bad;
			break;
		case PokemonType::GROUND:
			return DamageType::Nothing;
			break;
		case PokemonType::FLYING:
			return DamageType::Great;
			break;
		case PokemonType::DRAGON:
			return DamageType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::GRASS:
		switch (Defend)
		{
		case PokemonType::FIRE:
			return DamageType::Bad;
			break;
		case PokemonType::WATER:
			return DamageType::Great;
			break;
		case PokemonType::GRASS:
			return DamageType::Bad;
			break;
		case PokemonType::POISON:
			return DamageType::Bad;
			break;
		case PokemonType::GROUND:
			return DamageType::Great;
			break;
		case PokemonType::FLYING:
			return DamageType::Bad;
			break;
		case PokemonType::BUG:
			return DamageType::Bad;
			break;
		case PokemonType::ROCK:
			return DamageType::Great;
			break;
		case PokemonType::DRAGON:
			return DamageType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::ICE:
		switch (Defend)
		{
		case PokemonType::FIRE:
			return DamageType::Bad;
			break;
		case PokemonType::WATER:
			return DamageType::Bad;
			break;
		case PokemonType::GRASS:
			return DamageType::Great;
			break;
		case PokemonType::ICE:
			return DamageType::Bad;
			break;
		case PokemonType::GROUND:
			return DamageType::Great;
			break;
		case PokemonType::FLYING:
			return DamageType::Great;
			break;
		case PokemonType::DRAGON:
			return DamageType::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::FIGHTING:
		switch (Defend)
		{
		case PokemonType::NORMAL:
			return DamageType::Great;
			break;
		case PokemonType::ICE:
			return DamageType::Great;
			break;
		case PokemonType::POISON:
			return DamageType::Bad;
			break;
		case PokemonType::FLYING:
			return DamageType::Bad;
			break;
		case PokemonType::PSYCHIC:
			return DamageType::Bad;
			break;
		case PokemonType::BUG:
			return DamageType::Bad;
			break;
		case PokemonType::ROCK:
			return DamageType::Great;
			break;
		case PokemonType::GHOST:
			return DamageType::Nothing;
			break;
		default:
			break;
		}
		break;
	case PokemonType::POISON:
		switch (Defend)
		{
		case PokemonType::GRASS:
			return DamageType::Great;
			break;
		case PokemonType::POISON:
			return DamageType::Bad;
			break;
		case PokemonType::GROUND:
			return DamageType::Bad;
			break;
		case PokemonType::ROCK:
			return DamageType::Bad;
			break;
		case PokemonType::GHOST:
			return DamageType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::GROUND:
		switch (Defend)
		{
		case PokemonType::FIRE:
			return DamageType::Great;
			break;
		case PokemonType::ELECTRIC:
			return DamageType::Great;
			break;
		case PokemonType::GRASS:
			return DamageType::Bad;
			break;
		case PokemonType::POISON:
			return DamageType::Great;
			break;
		case PokemonType::FLYING:
			return DamageType::Nothing;
			break;
		case PokemonType::BUG:
			return DamageType::Bad;
			break;
		case PokemonType::ROCK:
			return DamageType::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::FLYING:
		switch (Defend)
		{
		case PokemonType::ELECTRIC:
			return DamageType::Bad;
			break;
		case PokemonType::GRASS:
			return DamageType::Great;
			break;
		case PokemonType::FIGHTING:
			return DamageType::Great;
			break;
		case PokemonType::BUG:
			return DamageType::Great;
			break;
		case PokemonType::ROCK:
			return DamageType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::PSYCHIC:
		switch (Defend)
		{
		case PokemonType::FIGHTING:
			return DamageType::Great;
			break;
		case PokemonType::POISON:
			return DamageType::Great;
			break;
		case PokemonType::PSYCHIC:
			return DamageType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::BUG:
		switch (Defend)
		{
		case PokemonType::FIRE:
			return DamageType::Bad;
			break;
		case PokemonType::GRASS:
			return DamageType::Great;
			break;
		case PokemonType::FIGHTING:
			return DamageType::Bad;
			break;
		case PokemonType::POISON:
			return DamageType::Bad;
			break;
		case PokemonType::FLYING:
			return DamageType::Bad;
			break;
		case PokemonType::PSYCHIC:
			return DamageType::Great;
			break;
		case PokemonType::GHOST:
			return DamageType::Bad;
			break;
		default:
			break;
		}
		break;
	case PokemonType::ROCK:
		switch (Defend)
		{
		case PokemonType::FIRE:
			return DamageType::Great;
			break;
		case PokemonType::ICE:
			return DamageType::Great;
			break;
		case PokemonType::FIGHTING:
			return DamageType::Bad;
			break;
		case PokemonType::GROUND:
			return DamageType::Bad;
			break;
		case PokemonType::FLYING:
			return DamageType::Great;
			break;
		case PokemonType::BUG:
			return DamageType::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::GHOST:
		switch (Defend)
		{
		case PokemonType::NORMAL:
			return DamageType::Nothing;
			break;
		case PokemonType::PSYCHIC:
			return DamageType::Great;
			break;
		case PokemonType::GHOST:
			return DamageType::Great;
			break;
		default:
			break;
		}
		break;
	case PokemonType::DRAGON:
		switch (Defend)
		{
		case PokemonType::DRAGON:
			return DamageType::Great;
			break;
		default:
			break;
		}
		break;
	}
	return DamageType::Nomal;
}