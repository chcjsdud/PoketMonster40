#include "PokemonInfoManager.h"

PokemonInfoManager* PokemonInfoManager::Inst_ = new PokemonInfoManager();

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

Pokemon* PokemonInfoManager::CreatePokemon()
{
	
	return nullptr;
}

PokemonSkill* PokemonInfoManager::CreateSkill()
{
	return nullptr;
}

Item* PokemonInfoManager::CreateItem()
{
	return nullptr;
}
