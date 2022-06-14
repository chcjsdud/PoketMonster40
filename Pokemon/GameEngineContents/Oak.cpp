#include "Oak.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "ContentEnum.h"
#include "NPCBase.h"
#include "WorldTileMap1.h"
#include "RoomTileMap4.h"
#include "PlayerRed.h"
#include "Green.h"
#include "InteractionText.h"

Oak::Oak()
	: IsStart_(false)
	, RedOutCheck_(false)
{
}

Oak::~Oak()
{
}

void Oak::Start()
{
	NPCCollision_ = CreateCollision("NPCColBox", { 60,60 });
	NPCUpCollision_ = CreateCollision("OakDirZColBox", { 20,5 }, { 0,-32 });
	NPCDownCollision_ = CreateCollision("OakDirZColBox", { 20,5 }, { 0,32 });
	NPCRightCollision_ = CreateCollision("OakDirZColBox", { 5,20 }, { 32,0 });
	NPCLeftCollision_ = CreateCollision("OakDirZColBox", { 5,20 }, { -32,0 });
	{
		GameEngineImage*
		// Idle
		Image = GameEngineImageManager::GetInst()->Find("Oak_Idle_Up.bmp");
		Image->Cut({ 56,80 });
		Image = GameEngineImageManager::GetInst()->Find("Oak_Idle_Down.bmp");
		Image->Cut({ 56,80 });
		Image = GameEngineImageManager::GetInst()->Find("Oak_Idle_Right.bmp");
		Image->Cut({ 52,80 });
		Image = GameEngineImageManager::GetInst()->Find("Oak_Idle_Left.bmp");
		Image->Cut({ 52,80 });

		// Walk
		Image = GameEngineImageManager::GetInst()->Find("Oak_Walk_Up.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("Oak_Walk_Down.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("Oak_Walk_Right.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("Oak_Walk_Left.bmp");
		Image->CutCount(3, 1);
	}

	NPCRender_ = CreateRenderer(static_cast<int>(RenderOrder::Player));
	NPCRender_->CreateAnimation("Oak_Idle_Up.bmp", "IdleUp", 0, 0, 0.0f, false);
	NPCRender_->CreateAnimation("Oak_Idle_Down.bmp", "IdleDown", 0, 0, 0.0f, false);
	NPCRender_->CreateAnimation("Oak_Idle_Right.bmp", "IdleRight", 0, 0, 0.0f, false);
	NPCRender_->CreateAnimation("Oak_Idle_Left.bmp", "IdleLeft", 0, 0, 0.0f, false);

	NPCRender_->CreateAnimation("Oak_Walk_Up.bmp", "WalkUp", 0, 2, 0.1f, true);
	NPCRender_->CreateAnimation("Oak_Walk_Down.bmp", "WalkDown", 0, 2, 0.1f, true);
	NPCRender_->CreateAnimation("Oak_Walk_Right.bmp", "WalkRight", 0, 2, 0.1f, true);
	NPCRender_->CreateAnimation("Oak_Walk_Left.bmp", "WalkLeft", 0, 2, 0.1f, true);

	NPCRender_->ChangeAnimation("WalkUp");
	NPCRender_->SetPivot({ 0,-15 });
	NPCRender_->Off();

	for (int i = 0; i < 20; i++)
	{
		IsStart_.push_back(false);
		IsStartShop_.push_back(false);
	}
	//CurrentTileMap_ = RoomTileMap4::GetInst();
	//SetPosition(RoomTileMap4::GetInst()->GetWorldPostion(6, 1));
}

void Oak::Update()
{
	NPCMoveAnim();
	RedCatch();
	OakFollow();
	Room4Enter();

	ShopEvent();
}

void Oak::OakMoveIndexPos(int _X, int _Y)
{

}

void Oak::RedCatch()
{
	if (true == RedOutCheck_)
	{
		PlayerRed::MainRed_->SetInteraction(true);
		// 오박사 월드맵1에서 레드 쫓아옴
		// 패턴 존재
		// 오박사의 시작 위치에서 (y-2 -> x+1) -> (y-2 -> x+1) -> y-2
		if (false == IsStart_[0])
		{
			IsStart_[0] = true;
			NPCRender_->On();
			OakCurrentIndexX_ = static_cast<int>(PlayerRed::MainRed_->GetRedCurrentIndex().x - 2);
			OakCurrentIndexY_ = static_cast<int>(PlayerRed::MainRed_->GetRedCurrentIndex().y + 7);
			CurrentTileMap_ = WorldTileMap1::GetInst();
			SetPosition(WorldTileMap1::GetInst()->GetWorldPostion(OakCurrentIndexX_, OakCurrentIndexY_));
			NPCMoveDir(NPCDir::Up, 2);
		}

		if (false == IsStart_[1] && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[1] = true;
			NPCMoveDir(NPCDir::Right, 1);
		}

		if (false == IsStart_[2] && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[2] = true;
			NPCMoveDir(NPCDir::Up, 2);
		}

		if (false == IsStart_[3] && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[3] = true;
			NPCMoveDir(NPCDir::Right, 1);
		}

		if (false == IsStart_[4] && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[4] = true;
			NPCMoveDir(NPCDir::Up, 2);
		}

		if (false == IsStart_[5] && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[5] = true;
			RedCatchEndCheck_ = true;
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(PlayerRed::MainRed_->GetPosition());
			TmpText->AddText("OAK: It's unsafe!");
			TmpText->AddText("Wild POKEMON live in tall grass!");
			TmpText->AddText("You need your own POKEMON for");
			TmpText->AddText("your protection.");
			TmpText->AddText("I know!");
			TmpText->AddText("Here, come with me!");
			TmpText->Setting();

			RedOutCheck_ = false;
		}
	}
}

void Oak::OakFollow()
{
	if (true == OakFollowCheck_)
	{
		int RedCurrentIndexX_;
		RedCurrentIndexX_ = PlayerRed::MainRed_->GetRedCurrentIndex().ix();

		if (false == IsStart_[6])
		{
			IsStart_[6] = true;
			NPCMoveDir(NPCDir::Down, 1);
			PlayerRed::MainRed_->RedMoveControll(RedDir::Down, 1);
		}


		if (false == IsStart_[7] && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[7] = true;
			NPCMoveDir(NPCDir::Left, 1);
			PlayerRed::MainRed_->RedMoveControll(RedDir::Down, 1);
		}

		if (false == IsStart_[8] && 21 == RedCurrentIndexX_ && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[8] = true;
			NPCMoveDir(NPCDir::Down, 1);
			PlayerRed::MainRed_->RedMoveControll(RedDir::Left, 1);
		}
		else if (false == IsStart_[8] && 22 == RedCurrentIndexX_ && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[8] = true;
			NPCMoveDir(NPCDir::Left, 1);
			PlayerRed::MainRed_->RedMoveControll(RedDir::Left, 1);
		}

		if (false == IsStart_[9] && 21 == RedCurrentIndexX_ && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[9] = true;
			NPCMoveDir(NPCDir::Down, 1);
			PlayerRed::MainRed_->RedMoveControll(RedDir::Down, 1);
		}
		else if (false == IsStart_[9] && 22 == RedCurrentIndexX_ && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[9] = true;
			NPCMoveDir(NPCDir::Down, 1);
			PlayerRed::MainRed_->RedMoveControll(RedDir::Left, 1);
		}

		if (false == IsStart_[10] && 21 == RedCurrentIndexX_ && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[10] = true;
			NPCMoveDir(NPCDir::Down, 9);
			PlayerRed::MainRed_->RedMoveControll(RedDir::Down, 9);
		}
		else if (false == IsStart_[10] && 22 == RedCurrentIndexX_ && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[10] = true;
			NPCMoveDir(NPCDir::Down, 10);
			PlayerRed::MainRed_->RedMoveControll(RedDir::Down, 10);
		}

		if (false == IsStart_[11] && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[11] = true;
			NPCMoveDir(NPCDir::Right, 1);
			PlayerRed::MainRed_->RedMoveControll(RedDir::Down, 1);
		}

		if (false == IsStart_[12] && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[12] = true;
			NPCMoveDir(NPCDir::Right, 4);
			PlayerRed::MainRed_->RedMoveControll(RedDir::Right, 4);
		}

		if (false == IsStart_[13] && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[13] = true;
			PlayerRed::MainRed_->SetFadeIn(true);
			NPCAnimationName_ = "Idle";
			NPCChangeDirText_ = "Up";
			NPCRender_->ChangeAnimation(NPCAnimationName_ + NPCChangeDirText_);
		}

		if (false == IsStart_[14] && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[14] = true;
			PlayerRed::MainRed_->SetFadeIn(true);
		}


		if (false == IsStart_[15] && GetAccTime() >= NextDirMoveTimer_ && true == PlayerRed::MainRed_->GetFadeOut())
		{
			IsStart_[15] = true;
			PlayerRed::MainRed_->SetCurrentTileMap(RoomTileMap4::GetInst());
			CurrentTileMap_ = RoomTileMap4::GetInst();

			SetPosition(CurrentTileMap_->GetWorldPostion(6, 9));
			PlayerRed::MainRed_->SetPosition(CurrentTileMap_->GetWorldPostion(6, 11));
			PlayerRed::MainRed_->RedMoveControll(RedDir::Up, 0);
			PlayerRed::MainRed_->SetControllOn(false);
			OakFollowCheck_ = false;
			Room4EnterCheck_ = true;
		}
	}
}

void Oak::Room4Enter()
{
	if (true == Room4EnterCheck_)
	{
		//PlayerRed::MainRed_->SetInteraction(true);
		if (false == IsStart_[16])
		{
			IsStart_[16] = true;
			NPCMoveDir(NPCDir::Up, 8);
			//PlayerRed::MainRed_->SetPosition(CurrentTileMap_->GetWorldPostion(6, 10));
		}

		if (false == IsStart_[17] && GetAccTime() >= NextDirMoveTimer_)
		{
			IsStart_[17] = true;

			NPCAnimationName_ = "Idle";
			NPCChangeDirText_ = "Down";
			NPCRender_->ChangeAnimation(NPCAnimationName_ + NPCChangeDirText_);

			//PlayerRed::MainRed_->RedMoveControll(RedDir::Up, 8);
			PlayerRed::MainRed_->SetRedMoveCheck(true);
		}

		if (false == IsStart_[18] && 2 == PlayerRed::MainRed_->GetCurrentTilePos().iy())
		{
			IsStart_[18] = true;
			PlayerRed::MainRed_->SetRedMoveCheck(false);
			PlayerRed::MainRed_->SetRedMoveEnd(true);
			PlayerRed::MainRed_->SetControllOn(false);

			Green::NPCGreen->NPCRender_->ChangeAnimation("IdleUp");
		}

		if (false == IsStart_[19] && true == PlayerRed::MainRed_->GetRedMoveEnd())
		{
			IsStart_[19] = true;

			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(PlayerRed::MainRed_->GetPosition() + float4(0, -60));
			TmpText->AddText("GREEN: Gramps!");
			TmpText->AddText("I'm fed up with waiting!");
			TmpText->AddText("OAK: GREEN?");
			TmpText->AddText("Let me Think...");
			TmpText->AddText("Oh, that's right, I told you to");
			TmpText->AddText("come! Just wait!");
			TmpText->AddText("Here, Red.");
			TmpText->AddText("");
			TmpText->AddText("There are three POKEMON here.");
			TmpText->AddText("");
			TmpText->AddText("Haha!");
			TmpText->AddText("");
			TmpText->AddText("The POKEMON are held inside");
			TmpText->AddText("these POKE BALLS.");
			TmpText->AddText("When I was Young, I was a serious");
			TmpText->AddText("POKEMON TRAINER.");
			TmpText->AddText("But now, in my old age, I have");
			TmpText->AddText("only these three left.");
			TmpText->AddText("You can have one.");
			TmpText->AddText("Go on, choose!");
			TmpText->AddText("GREEN: Hey! Gramps! No fair!");
			TmpText->AddText("What about me?");
			TmpText->AddText("OAK: Be patient, GREEN.");
			TmpText->AddText("You can have one, too!");
			TmpText->Setting();
		}

		OakFollowCheck_ = false;
	}
}

