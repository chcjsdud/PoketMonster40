#include "BattlePokemon.h"

BattlePokemon::BattlePokemon() 
	: PlayerPokemon_(nullptr)
	, OpponentPokemon_(nullptr)
{
}

BattlePokemon::~BattlePokemon() 
{
}

void BattlePokemon::Start()
{
	PlayerPokemon_ = CreateRenderer("");
	OpponentPokemon_ = CreateRenderer("");

}

void BattlePokemon::Update()
{

}