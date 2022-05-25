#include "NPC4.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "NPCBase.h"
//#include "RoomTileMap1.h"
#include "WorldTileMap1.h"

NPC4::NPC4() 
{
}

NPC4::~NPC4() 
{
}

void NPC4::Start()
{
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

	NPCRender_ = CreateRenderer();
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
	//SetPosition(RoomTileMap1::GetInst()->GetWorldPostion(8, 4));
	
	NPCBase::InSideLeftTop_ = { 16,96 };
	NPCBase::InSideRightBot_ = { 30,100 };
	//NPCBase::InSideLeftTop_ = { 3,3 };
	//NPCBase::InSideRightBot_ = { 8,6 };

	CurrentTileMap_ = WorldTileMap1::GetInst();
	SetPosition(WorldTileMap1::GetInst()->GetWorldPostion(20, 100));

	NPCBase::IsInside(NPCBase::InSideLeftTop_, NPCBase::InSideRightBot_);
	
}

void NPC4::Update()
{
	NPCBase::NPCMoveAnim();
	NPCBase::NPCMove();
}

