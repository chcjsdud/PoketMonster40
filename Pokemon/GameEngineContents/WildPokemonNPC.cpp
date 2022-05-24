#include "WildPokemonNPC.h"
#include "Pokemon.h"

WildPokemonNPC::WildPokemonNPC()
{
	SetBattleNPC(true);
}

WildPokemonNPC::~WildPokemonNPC() 
{
	for (auto* Pokemon : CurrentPossessionPokemons_)
	{
		if (Pokemon != nullptr)
		{
			Pokemon->Death();
		}
	}
	
}

