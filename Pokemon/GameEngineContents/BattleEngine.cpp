#include "BattleEngine.h"


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

float BattleEngine::AttackCalculation(const PokemonBattleState* _Att, PokemonBattleState* _Def, const PokemonSkill& _Skill)
{
	// int _Att->
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