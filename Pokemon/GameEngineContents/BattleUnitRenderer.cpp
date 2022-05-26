#include "BattleUnitRenderer.h"
#include "GameEngineBase/GameEngineWindow.h"
#include "GameEngineBase/GameEngineTime.h"
#include <GameEngine/GameEngineImageManager.h>

GameEngineRenderer* BattleUnitRenderer::PlayerRenderer_ = nullptr;

BattleUnitRenderer::BattleUnitRenderer() 
	: PlayerCurrentPokemon_(nullptr)
	, PoeCurrentPokemon_(nullptr)
	, OpponentRenderer_(nullptr)
	, FirstMove(true)
	, PlayerPokemonPos_({ -220, 60 })
	, OpponentPokemonPos_({ 200, -105 })
	, PlayerRendererPos_({ 480,31 })
	, OpponentRenderer_Pos_()
	, MoveSpeed(200.0f)
	, PlayerStop(false)
{
}

BattleUnitRenderer::~BattleUnitRenderer() 
{
}

void BattleUnitRenderer::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half() });
	PlayerCurrentPokemon_ = CreateRenderer("SquirtleB.bmp", 3, RenderPivot::CENTER, PlayerPokemonPos_);
	PoeCurrentPokemon_ = CreateRenderer("BulbasaurF.bmp", 3, RenderPivot::CENTER, OpponentPokemonPos_);

	PlayerRenderer_ = CreateRenderer("Player.bmp", 4, RenderPivot::CENTER, PlayerRendererPos_);
	
	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("PlayerAnimation.bmp");
	Image->CutCount(5, 1);

	PlayerRenderer_->CreateAnimation("PlayerAnimation.bmp", "Go", 0, 4, 0.1f, false);
}

void BattleUnitRenderer::Update()
{
	if (FirstMove == true)
	{
		PlayerTime_ += GameEngineTime::GetDeltaTime() * MoveSpeed;
		PlayerRenderer_->SetPivot({ 480 - PlayerTime_, 31 });
		if (PlayerRenderer_->GetPivot().x <= -200.0f)//float은 정확하게 딱맞아 떨어지지 않는다
		{
			MoveSpeed = 0.0f;
			PlayerStop = true;
			
			FirstMove = false;
		}

	}
}