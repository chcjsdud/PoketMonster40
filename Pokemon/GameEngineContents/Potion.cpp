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
	_MyPokemon->PlusHp(GetValue());
}

void Potion::Use()
{
}

