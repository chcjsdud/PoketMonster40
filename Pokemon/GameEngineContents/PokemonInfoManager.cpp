#include "PokemonInfoManager.h"
#include "Pokemon.h"

PokemonInfoManager::PokemonInfoManager() 
{
}

PokemonInfoManager::~PokemonInfoManager() 
{
}

void PokemonInfoManager::Reset()
{
	
}

void PokemonInfoManager::Update()
{
}

Pokemon* PokemonInfoManager::CreatePokemon(std::string _Key, PokemonType _Type, StatusEffect _Effect, int _Lv, int _Att, int _Def, int _SpAtt, int _SpDef, int _Speed)
{
	Pokemon* NewPokemon = new Pokemon();
	//NewPokemon->SetName

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

