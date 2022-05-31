#include "NPC6.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>

#include "NPCBase.h"
#include "RoomTileMap5.h"

NPC6::NPC6() 
{
}

NPC6::~NPC6() 
{
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

	NPCRender_ = CreateRenderer();
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

	//NPCBase::InSideLeftTop_ = { 16,96 };
	//NPCBase::InSideRightBot_ = { 30,102 };


	CurrentTileMap_ = RoomTileMap5::GetInst();
	SetPosition(RoomTileMap5::GetInst()->GetWorldPostion(7, 0));
}

void NPC6::Update()
{
}

