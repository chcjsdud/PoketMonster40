#include "BattleNPCInterface.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "Pokemon.h"

BattleNPCInterface::BattleNPCInterface()
	: BattleNPC_(false)
{

}

BattleNPCInterface::~BattleNPCInterface() 
{
	for (auto* Pokemon : CurrentPossessionPokemons_)
	{
		if (Pokemon != nullptr)
		{
			Pokemon->Death();
		}
	}
}
