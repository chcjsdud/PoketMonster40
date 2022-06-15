#include "NPC4.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "NPCBase.h"
#include "WorldTileMap1.h"
#include "ContentEnum.h"

NPC4::NPC4() 
{
}

NPC4::~NPC4() 
{
}

void NPC4::Start()
{
	NPCBase::NPCCollision_ = CreateCollision("NPCColBox", { 60,60 });
	NPCBase::NPCUpCollision_ = CreateCollision("NPC4DirZColBox", { 20,5 }, { 0,-32 });
	NPCBase::NPCDownCollision_ = CreateCollision("NPC4DirZColBox", { 20,5 }, { 0,32 });
	NPCBase::NPCRightCollision_ = CreateCollision("NPC4DirZColBox", { 5,20 }, { 32,0 });
	NPCBase::NPCLeftCollision_ = CreateCollision("NPC4DirZColBox", { 5,20 }, { -32,0 });
	{
		GameEngineImage*
		// Idle
		Image = GameEngineImageManager::GetInst()->Find("NPC4_.bmp");
		Image->Cut({ 128,128 });

		// Walk
		Image = GameEngineImageManager::GetInst()->Find("NPC4_walk_up.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("NPC4_walk_down.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("NPC4_walk_right.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("NPC4_walk_left.bmp");
		Image->CutCount(3, 1);
	}

	NPCRender_ = CreateRenderer(static_cast<int>(RenderOrder::Player));
	NPCRender_->CreateAnimation("NPC4_.bmp", "IdleDown", 0, 0, 0.0f, false);
	NPCRender_->CreateAnimation("NPC4_.bmp", "IdleLeft", 1, 1, 0.0f, false);
	NPCRender_->CreateAnimation("NPC4_.bmp", "IdleRight", 2, 2, 0.0f, false);
	NPCRender_->CreateAnimation("NPC4_.bmp", "IdleUp", 3, 3, 0.0f, false);
	
	NPCRender_->CreateAnimation("NPC4_walk_up.bmp", "WalkUp", 0, 2, 0.1f, true);
	NPCRender_->CreateAnimation("NPC4_walk_down.bmp", "WalkDown", 0, 2, 0.1f, true);
	NPCRender_->CreateAnimation("NPC4_walk_right.bmp", "WalkRight", 0, 2, 0.1f, true);
	NPCRender_->CreateAnimation("NPC4_walk_left.bmp", "WalkLeft", 0, 2, 0.1f, true);

	NPCRender_->ChangeAnimation("IdleDown");
	NPCRender_->SetPivot({ 0,-15 });
	
	NPCBase::InSideLeftTop_ = { 16,99 };
	NPCBase::InSideRightBot_ = { 30,102 };

	CurrentTileMap_ = WorldTileMap1::GetInst();
	SetPosition(WorldTileMap1::GetInst()->GetWorldPostion(22, 101));

	NPCBase::IsInside(NPCBase::InSideLeftTop_, NPCBase::InSideRightBot_);
	
}

void NPC4::Update()
{
	NPCBase::NPCMoveAnim();
	NPCBase::NPCMove();
}