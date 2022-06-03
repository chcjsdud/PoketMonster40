#include "Potion.h"
#include "Pokemon.h"

Potion::Potion() 
{
}

Potion::~Potion() 
{
}

void Potion::Recovery(PokemonInfo* _MyPokemon)
{
	_MyPokemon->PlusHp(GetInfo()->GetValue());
}

void Potion::Use()
{
	//상처약 기능
}

