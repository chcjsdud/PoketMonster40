#include "BattleUnitRenderer.h"
#include "GameEngineBase/GameEngineWindow.h"

BattleUnitRenderer::BattleUnitRenderer() 
	: PlayerPokemon_(nullptr)
	, OpponentPokemon_(nullptr)
	, OpponentRenderer_(nullptr)
	, PlayerRenderer_(nullptr)
	, PlayerPokemonPos_({ -220, 60 })
	, OpponentPokemonPos_({ 200, -105 })
	, PlayerRendererPos_()
	, OpponentRenderer_Pos_()
{
}

BattleUnitRenderer::~BattleUnitRenderer() 
{
}

void BattleUnitRenderer::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half() });
	PlayerPokemon_ = CreateRenderer("SquirtleB.bmp", 3, RenderPivot::CENTER, PlayerPokemonPos_);
	OpponentPokemon_ = CreateRenderer("BulbasaurF.bmp", 3, RenderPivot::CENTER, OpponentPokemonPos_);

}

void BattleUnitRenderer::Update()
{

}