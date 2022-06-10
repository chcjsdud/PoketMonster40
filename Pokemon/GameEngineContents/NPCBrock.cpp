#include "NPCBrock.h"
#include "GymTileMap.h"

NPCBrock::NPCBrock() 
{
}

NPCBrock::~NPCBrock() 
{
}

void NPCBrock::Start()
{
	NPCBase::NPCCollision_ = CreateCollision("NPCColBox", { 60,60 });
	NPCBase::NPCUpCollision_ = CreateCollision("NPCBrockDirZColBox", { 20,5 }, { 0,-32 });
	NPCBase::NPCDownCollision_ = CreateCollision("NPCBrockDirZColBox", { 20,5 }, { 0,32 });
	NPCBase::NPCRightCollision_ = CreateCollision("NPCBrockDirZColBox", { 5,20 }, { 32,0 });
	NPCBase::NPCLeftCollision_ = CreateCollision("NPCBrockDirZColBox", { 5,20 }, { -32,0 });
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("NPC4_.bmp");
		Image->Cut({ 128,128 });
	}

	NPCRender_ = CreateRenderer();
	NPCRender_->CreateAnimation("NPC4_.bmp", "IdleDown", 0, 0, 0.0f, false);
	NPCRender_->CreateAnimation("NPC4_.bmp", "IdleLeft", 1, 1, 0.0f, false);
	NPCRender_->CreateAnimation("NPC4_.bmp", "IdleRight", 2, 2, 0.0f, false);
	NPCRender_->CreateAnimation("NPC4_.bmp", "IdleUp", 3, 3, 0.0f, false);

	NPCRender_->ChangeAnimation("IdleDown");
	NPCRender_->SetPivot({ 0,-15 });

	CurrentTileMap_ = GymTileMap::GetInst();
	SetPosition(GymTileMap::GetInst()->GetWorldPostion(11, 10));

	NPCBase::IsInside(NPCBase::InSideLeftTop_, NPCBase::InSideRightBot_);
}

void NPCBrock::Update()
{
	NPCInteractDir();
}
