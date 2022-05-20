#include "BattleUnitRenderer.h"
#include "GameEngineBase/GameEngineWindow.h"
#include "GameEngineBase/GameEngineTime.h"

BattleUnitRenderer::BattleUnitRenderer() 
	: PlayerPokemon_(nullptr)
	, OpponentPokemon_(nullptr)
	, OpponentRenderer_(nullptr)
	, PlayerRenderer_(nullptr)
	, PlayerPokemonPos_({ -220, 60 })
	, OpponentPokemonPos_({ 200, -105 })
	, PlayerRendererPos_({ 480,31 })
	, OpponentRenderer_Pos_()
	, MoveSpeed(200.0f)
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

	PlayerRenderer_ = CreateRenderer("Player.bmp", 4, RenderPivot::CENTER, PlayerRendererPos_);
}

void BattleUnitRenderer::Update()
{
	PlayerTime_ += GameEngineTime::GetDeltaTime()*MoveSpeed;
	PlayerRenderer_->SetPivot({ 480 - PlayerTime_, 31 });
	if (PlayerRenderer_->GetPivot().x <= -200.0f)//float은 정확하게 딱맞아 떨어지지 않는다
	{
		MoveSpeed = 0.0f;
	}
}