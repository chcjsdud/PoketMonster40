#include "PokemonInfoManager.h"
#include "Pokemon.h"
#include <GameEngineBase/GameEngineString.h>

PokemonInfoManager* PokemonInfoManager::Inst_ = new PokemonInfoManager();

PokemonInfoManager::PokemonInfoManager() 
{
}

PokemonInfoManager::~PokemonInfoManager() 
{
	std::map<std::string, Pokemon*>::iterator StartIter = AllPokemonList_.begin();
	std::map<std::string, Pokemon*>::iterator EndIter = AllPokemonList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

}

void PokemonInfoManager::Reset()
{
	{
		//Charmander: 颇捞府
		CreatePokemon("Charmander", PokemonType::FIRE, 1, 10, 10, 15, 15, 5);
		//Squirtle: 部何扁
		CreatePokemon("Squirtle", PokemonType::WATER, 1, 10, 10, 15, 15, 5);
		//Bulbasaur: 捞惑秦揪
		CreatePokemon("Bulbasaur", PokemonType::GRASS, 1, 10, 10, 15, 15, 5);
		//Pidgey: 备备
		CreatePokemon("Pidgey", PokemonType::FLYING, 1, 10, 10, 15, 15, 5);
		//Rattata: 部房
		CreatePokemon("Rattata", PokemonType::NORMAL, 1, 10, 10, 15, 15, 5);
	}

	Pokemon* Pokemon_ = FindPokemon("Rattata");
}

void PokemonInfoManager::Update()
{

}

Pokemon* PokemonInfoManager::FindPokemon(const std::string _Key)
{
	std::string Key = GameEngineString::ToUpperReturn(_Key);

	std::map<std::string, Pokemon*>::iterator FindIter = AllPokemonList_.find(Key);

	if (FindIter == AllPokemonList_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

Pokemon* PokemonInfoManager::CreatePokemon(const std::string _Key, PokemonType _Type, int _Lv, int _Att, int _Def, int _SpAtt, int _SpDef, int _Speed)
{
	Pokemon* NewPokemon = new Pokemon();

	std::string Key = GameEngineString::ToUpperReturn(_Key);

	NewPokemon->SetName(Key);
	NewPokemon->SetMyType(_Type);
	NewPokemon->SetStatusEffect(StatusEffect::NONE);
	NewPokemon->SetMyLevel(_Lv);
	NewPokemon->SetMyMaxLevel(100);
	NewPokemon->SetHp(100);
	NewPokemon->SetMaxHp(100);
	NewPokemon->SetExp(0);
	NewPokemon->SetMaxExp(0);
	NewPokemon->SetAtt(_Att);
	NewPokemon->SetDef(_Def);
	NewPokemon->SetSpAtt(_SpAtt);
	NewPokemon->SetSpDef(_SpDef);
	NewPokemon->SetSpeed(_Speed);
	NewPokemon->SetIsPlayer(false);
	NewPokemon->SetIsGender(false);

	AllPokemonList_.insert(std::make_pair(Key, NewPokemon));

	return NewPokemon;
}

PokemonSkill* PokemonInfoManager::CreateSkill()
{
	return nullptr;
}

Item* PokemonInfoManager::CreateItem()
{
	return nullptr;
}

