#include "Potion.h"
#include "Pokemon.h"

Potion::Potion() 
{
}

Potion::~Potion() 
{
}

void Potion::Recovery(Pokemon* _MyPokemon)
{
	_MyPokemon->PlusHp(GetValue());
}

