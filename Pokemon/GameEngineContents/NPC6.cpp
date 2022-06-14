#include "NPC6.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>

#include "NPCBase.h"
#include "PlayerRed.h"
#include "RoomTileMap5.h"
#include "InteractionText.h"
#include "ContentEnum.h"
#include "WorldMapSoundManager.h"

bool NPC6::InteractionMove_ = false;
bool NPC6::InteractionAnim_ = false;
InteractionText* NPC6::Text_ = nullptr;

NPC6::NPC6() 
	: PokeBallEffect_(false)
	, InteractionTime_(0.0f)
{
}

NPC6::~NPC6() 
{
}

void NPC6::InteractionMove()
{
	if (true == InteractionMove_)
	{
		InteractionTime_ += GameEngineTime::GetDeltaTime();

		if (false == NPCRender_->IsAnimationName("IdleLeft"))
		{
			PokemonCenterBall->On();
			
			NPCRender_->ChangeAnimation("IdleLeft");
		}

		if (true == NPCRender_->IsAnimationName("IdleLeft") && 0.5f <= InteractionTime_)
		{
			if (false == PokeBallEffect_)
			{
				PokeBallEffect_ = true;
				PokemonCenterBallEffect->On();
			}
		}

		if (2.0f <= InteractionTime_)
		{
			NPCRender_->ChangeAnimation("IdleDown");
			InteractionTime_ = 0.0f;
			InteractionMove_ = false;
			Text_->ClearText();
			Text_->AddText("Thank you for waiting.");
			Text_->AddText("We've restored your POKEMON to");
			Text_->AddText("full health.");
			Text_->Setting();
			Text_->ZIgnore_ = false;
			InteractionText::IsCenterMove_ = false;
			PokeBallEffect_ = false;
			PokemonCenterBall->Off();
			PokemonCenterBallEffect->Off();

			// 포켓몬 체력 회복
			PlayerRed::MainRed_->GetPokemonList();

			return;
		}
	}
}

void NPC6::InteractionAnim()
{
	if (true == InteractionAnim_)
	{
		InteractionTime_ += GameEngineTime::GetDeltaTime();

		if (nullptr == Text_)
		{
			return;
		}

		if (false == NPCRender_->IsAnimationName("Anim"))
		{
			NPCRender_->ChangeAnimation("Anim");
		}

		if (1.0f <= InteractionTime_)
		{
			NPCRender_->ChangeAnimation("IdleDown");
			InteractionTime_ = 0.0f;
			InteractionAnim_ = false;
			Text_->ClearText();
			Text_->AddText("We hope to see you again!");
			Text_->Setting();
			Text_->ZIgnore_ = false;
			InteractionText::IsCenterAnim_ = false;
			return;
		}
	}
}

void NPC6::Start()
{
	//NPCBase::NPCCollision_ = CreateCollision("NPCColBox", { 60,60 });
	//NPCBase::NPCUpCollision_ = CreateCollision("NPC4DirZColBox", { 20,5 }, { 0,-32 });
	//NPCBase::NPCDownCollision_ = CreateCollision("NPC4DirZColBox", { 20,5 }, { 0,32 });
	//NPCBase::NPCRightCollision_ = CreateCollision("NPC4DirZColBox", { 5,20 }, { 32,0 });
	//NPCBase::NPCLeftCollision_ = CreateCollision("NPC4DirZColBox", { 5,20 }, { -32,0 });
	{
		GameEngineImage*
		// Idle
		Image = GameEngineImageManager::GetInst()->Find("NPC6_.bmp");
		Image->Cut({ 128,128 });

		Image = GameEngineImageManager::GetInst()->Find("NPC6_Anim.bmp");
		Image->Cut({ 128,128 });
		
		Image = GameEngineImageManager::GetInst()->Find("PokemonCenter_Anim.bmp");
		Image->Cut({ 128,128 });
		// Walk
		//Image = GameEngineImageManager::GetInst()->Find("NPC4_walk_up.bmp");
		//Image->CutCount(3, 1);
		//Image = GameEngineImageManager::GetInst()->Find("NPC4_walk_down.bmp");
		//Image->CutCount(3, 1);
		//Image = GameEngineImageManager::GetInst()->Find("NPC4_walk_right.bmp");
		//Image->CutCount(3, 1);
		//Image = GameEngineImageManager::GetInst()->Find("NPC4_walk_left.bmp");
		//Image->CutCount(3, 1);
	}

	NPCRender_ = CreateRenderer(static_cast<int>(RenderOrder::Player));
	NPCRender_->CreateAnimation("NPC6_.bmp", "IdleDown", 0, 0, 0.0f, false);
	NPCRender_->CreateAnimation("NPC6_.bmp", "IdleLeft", 1, 1, 0.0f, false);
	//NPCRender_->CreateAnimation("NPC4_.bmp", "IdleRight", 2, 2, 0.0f, false);
	//NPCRender_->CreateAnimation("NPC4_.bmp", "IdleUp", 3, 3, 0.0f, false);

	NPCRender_->CreateAnimation("NPC6_Anim.bmp", "Anim", 0, 0, 0.0f, false);
	//NPCRender_->CreateAnimation("NPC4_walk_up.bmp", "WalkUp", 0, 2, 0.1f, true);
	//NPCRender_->CreateAnimation("NPC4_walk_down.bmp", "WalkDown", 0, 2, 0.1f, true);
	//NPCRender_->CreateAnimation("NPC4_walk_right.bmp", "WalkRight", 0, 2, 0.1f, true);
	//NPCRender_->CreateAnimation("NPC4_walk_left.bmp", "WalkLeft", 0, 2, 0.1f, true);

	NPCRender_->ChangeAnimation("IdleDown");
	NPCRender_->SetPivot({ 0,-12 });

	PokemonCenterBall = CreateRenderer(static_cast<int>(RenderOrder::UI));
	PokemonCenterBall->CreateAnimation("PokemonCenter_Anim.bmp", "PokemonCenterBall1", 5, 5, 0.0f, false);
	PokemonCenterBall->ChangeAnimation("PokemonCenterBall1");
	PokemonCenterBall->SetPivot({ float4(-99,-32) });
	PokemonCenterBall->Off();

	PokemonCenterBallEffect = CreateRenderer(static_cast<int>(RenderOrder::UI));
	PokemonCenterBallEffect->CreateAnimation("PokemonCenter_Anim.bmp", "PokemonCenterBallEffect", 0, 4, 0.1f, true);
	PokemonCenterBallEffect->ChangeAnimation("PokemonCenterBallEffect");
	PokemonCenterBallEffect->SetPivot({ float4(-111,-48) });
	PokemonCenterBallEffect->Off();
	
	//NPCBase::InSideLeftTop_ = { 16,96 };
	//NPCBase::InSideRightBot_ = { 30,102 };


	CurrentTileMap_ = RoomTileMap5::GetInst();
	SetPosition(RoomTileMap5::GetInst()->GetWorldPostion(7, 0));
}

void NPC6::Update()
{
	InteractionMove();
	InteractionAnim();
}

