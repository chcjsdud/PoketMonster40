#include "NPCBrock.h"
#include "GymTileMap.h"
#include "PokemonInfoManager.h"
#include <GameEngineBase/GameEngineInput.h>

NPCBrock* NPCBrock::Inst_ = nullptr;

NPCBrock::NPCBrock()
{
	Inst_ = this;
}

NPCBrock::~NPCBrock() 
{
}

void NPCBrock::Start()
{
	SetBattleNPC(true);
	PushPokemon(PokemonInfoManager::GetInst().CreatePokemon("Geodude"));
	PushPokemon(PokemonInfoManager::GetInst().CreatePokemon("Onix"));

	NPCBase::NPCCollision_ = GameEngineActor::CreateCollision("NPCColBox", { 60,60 });
	NPCBase::NPCUpCollision_ = GameEngineActor::CreateCollision("NPCBrockDirZColBox", { 20,5 }, { 0,-32 });
	NPCBase::NPCDownCollision_ = GameEngineActor::CreateCollision("NPCBrockDirZColBox", { 20,5 }, { 0,32 });
	NPCBase::NPCRightCollision_ = GameEngineActor::CreateCollision("NPCBrockDirZColBox", { 5,20 }, { 32,0 });
	NPCBase::NPCLeftCollision_ = GameEngineActor::CreateCollision("NPCBrockDirZColBox", { 5,20 }, { -32,0 });
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Ungx4.bmp");
		Image->CutCount(4, 1);
	}

	NPCRender_ = GameEngineActor::CreateRenderer(static_cast<int>(RenderOrder::Player));
	NPCRender_->CreateAnimation("Ungx4.bmp", "IdleDown", 0, 0, 0.0f, false);
	NPCRender_->CreateAnimation("Ungx4.bmp", "IdleLeft", 2, 2, 0.0f, false);
	NPCRender_->CreateAnimation("Ungx4.bmp", "IdleRight", 3, 3, 0.0f, false);
	NPCRender_->CreateAnimation("Ungx4.bmp", "IdleUp", 1, 1, 0.0f, false);

	NPCRender_->ChangeAnimation("IdleDown");
	NPCRender_->SetPivot({ 0,-15 });

	CurrentTileMap_ = GymTileMap::GetInst();
	GameEngineActor::SetPosition(GymTileMap::GetInst()->GetWorldPostion(11, 10));

	NPCBase::IsInside(NPCBase::InSideLeftTop_, NPCBase::InSideRightBot_);
}

void NPCBrock::Update()
{
	NPCInteractDir();
}

GameEngineActor* NPCBrock::GetActor()
{
	return this;
}
