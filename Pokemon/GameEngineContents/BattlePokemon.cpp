#include "BattlePokemon.h"
#include "GameEngineBase/GameEngineWindow.h"

BattlePokemon::BattlePokemon() 
	: PlayerPokemon_(nullptr)
	, OpponentPokemon_(nullptr)
	, PlayerPokemonPos_({ -220, 60 })
	, OpponentPokemonPos_({ 200, -105 })
{
}

BattlePokemon::~BattlePokemon() 
{
}

void BattlePokemon::Start()
{
	SetPosition({GameEngineWindow::GetScale().Half()});
	PlayerPokemon_ = CreateRenderer("SquirtleB.bmp", 3 , RenderPivot::CENTER, PlayerPokemonPos_);
	OpponentPokemon_ = CreateRenderer("BulbasaurF.bmp", 3, RenderPivot::CENTER, OpponentPokemonPos_);

}

void BattlePokemon::Update()
{

}