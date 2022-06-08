#include "PlayerRed.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "WorldMapSoundManager.h"
#include "RoomTileMap1.h"
#include "RoomTileMap2.h"
#include "RoomTileMap3.h"
#include "RoomTileMap4.h"
#include "RoomTileMap5.h"
#include "RoomTileMap6.h"
#include "RoomTileMap7.h"
#include "RoomTileMap8.h"
#include "WorldTileMap1.h"
#include "WorldTileMap2.h"
#include "WorldTileMap3.h"

#include "InteractionText.h"
#include "Bush.h"
#include "NPCBase.h"

#include "Bag.h"
#include "PokemonMenu.h"
#include "MenuUI.h"
#include "FadeActor.h"

#include "PokemonInfoManager.h"
#include "PokemonInfo.h"
#include "Pokemon.h"

PlayerRed* PlayerRed::MainRed_ = nullptr;
bool PlayerRed::WMenuUICheck_ = true;
PlayerRed::PlayerRed()
	: CurrentDir_()
	, CurrentState_()
	, CurrentTileMap_()
	, RedRender_(nullptr)
	, ShadowRender_(nullptr)
	, FadeRender_(nullptr)
	, FadeRightRender_(nullptr)
	, FadeLeftRender_(nullptr)
	, AnimTimer_(0.0f)
	, WMenuArrowRender_()
	, WMenuUIRender_()
	//, WMenuUICheck_(true)
	, LerpTime_(0)
	, FadeTime_(0)
	, Alpha_()
	, MyPokemonList_{}
	, MyItemList_{}
	, IsFadeIn_(false)
	, IsFadeOut_(false)
	, IsFadeRL_(false)
	, IsFadeRLCheck_(false)
	, NPC5Check_(false)
	, LerpX_(0)
	, LerpY_(0)
	, MoveTimer_(0.0f)
	, NextMoveTime_(0.0f)
	, IsJump_(false)
	, IsMove_(false)
	, IsInteraction_(false)
	, IsBush_(false)
	, IsBushEventReady_(false)
	, IsDebugRun_(false)
	, IsPokemonMenuOn_(false)
	, BushActor_(nullptr)
	, BeforeTileMap_(nullptr)
	, NextTileMap_(nullptr)
	, ChildUI_(nullptr)
	, FadeActor_(nullptr)
	, RedCollision_(nullptr)
	, RedFrontCollision_(nullptr)
{
	MainRed_ = this;
}

PlayerRed::~PlayerRed()
{

}

void PlayerRed::ChangeState(RedState _State)
{
	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case RedState::Idle:
			IdleStart();
			break;
		case RedState::Walk:
			WalkStart();
			break;
		case RedState::Run:
			RunStart();
			break;
		case RedState::Max:
			break;
		default:
			break;
		}
	}
	AnimTimer_ = 0.0f;
	CurrentState_ = _State;
}

void PlayerRed::StateUpdate()
{
	switch (CurrentState_)
	{
	case RedState::Idle:
		IdleUpdate();
		break;
	case RedState::Walk:
		WalkUpdate();
		break;
	case RedState::Run:
		RunUpdate();
		break;
	case RedState::Max:
		break;
	default:
		break;
	}
}

void PlayerRed::DirAnimationCheck()
{
	if (false == CanMove())
	{
		return;
	}

	RedDir CheckDir_ = CurrentDir_;

	if (true == GameEngineInput::GetInst()->IsPress("Up"))
	{
		CheckDir_ = RedDir::Up;
		ChangeDirText_ = "Up";
		RedFrontCollision_->SetScale({ 20,5 });
		RedFrontCollision_->SetPivot({ 0,-32 });
	}
	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		CheckDir_ = RedDir::Down;
		ChangeDirText_ = "Down";
		RedFrontCollision_->SetScale({ 20,5 });
		RedFrontCollision_->SetPivot({ 0,32 });
	}
	if (true == GameEngineInput::GetInst()->IsPress("Right"))
	{
		CheckDir_ = RedDir::Right;
		ChangeDirText_ = "Right";
		RedFrontCollision_->SetScale({ 5,20 });
		RedFrontCollision_->SetPivot({ 32,0 });
	}
	if (true == GameEngineInput::GetInst()->IsPress("Left"))
	{
		CheckDir_ = RedDir::Left;
		ChangeDirText_ = "Left";
		RedFrontCollision_->SetScale({ 5,20 });
		RedFrontCollision_->SetPivot({ -32,0 });
	}

	if (CheckDir_ != CurrentDir_)
	{
		RedRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
		CurrentDir_ = CheckDir_;
	}
}

void PlayerRed::FadeIn()
{
	if (false == IsFadeIn_)
	{
		return;
	}

	if (true == IsFadeIn_)
	{
		Alpha_ += 255 * GameEngineTime::GetDeltaTime() * 1.0f;

		FadeRender_->On();
		FadeRender_->SetAlpha(static_cast<unsigned int>(Alpha_));

		if (255 <= Alpha_)
		{
			Alpha_ = 255;
			//FadeRender_->Off();
			IsFadeIn_ = false;
			IsFadeOut_ = true;
			if (nullptr != NextTileMap_)
			{
				BeforeTileMap_ = CurrentTileMap_;
				CurrentTileMap_ = NextTileMap_;
				SetPosition(CurrentTileMap_->GetWorldPostion(NextTilePos_.ix(), NextTilePos_.iy()));

				NextTileMap_ = nullptr;
				NextTilePos_ = float4::ZERO;
			}
			if (true == IsFadeRLCheck_)
			{
				IsFadeRL_ = true;
				FadeTime_ = 0;
			}
		}
	}
}

void PlayerRed::FadeOut()
{
	if (true == IsFadeOut_)
	{
		Alpha_ -= 255 * GameEngineTime::GetDeltaTime() * 1.0f;

		if (0 >= Alpha_)
		{
			Alpha_ = 0;
			IsFadeOut_ = false;
		}

		FadeRender_->SetAlpha(static_cast<unsigned int>(Alpha_));
	}
}

void PlayerRed::FadeRL()
{
	if (true == IsFadeRL_)
	{
		FadeTime_ += GameEngineTime::GetDeltaTime() * 300;
		FadeRightRender_->On();
		FadeLeftRender_->On();
		FadeRightRender_->SetPivot({ 0 + FadeTime_, 0 });
		FadeLeftRender_->SetPivot({ 0 - FadeTime_,0 });

		if (FadeRightRender_->GetPivot().x >= 500)
		{
			IsFadeRLCheck_ = false;
			IsFadeRL_ = false;
			return;
		}
	}
}

void PlayerRed::Start()
{
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IdleUp.bmp");
		Image->Cut({ 56,76 });
		Image = GameEngineImageManager::GetInst()->Find("IdleDown.bmp");
		Image->Cut({ 56,76 });
		Image = GameEngineImageManager::GetInst()->Find("IdleLeft.bmp");
		Image->Cut({ 56,76 });
		Image = GameEngineImageManager::GetInst()->Find("IdleRight.bmp");
		Image->Cut({ 56,76 });

		Image = GameEngineImageManager::GetInst()->Find("WalkUp.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("WalkDown.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("WalkLeft.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("WalkRight.bmp");
		Image->CutCount(3, 1);

		Image = GameEngineImageManager::GetInst()->Find("RunUp.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("RunDown.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("RunLeft.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("RunRight.bmp");
		Image->CutCount(3, 1);
	}

	GameEngineInput::GetInst()->CreateKey("JBMTest", 'L');
	GameEngineInput::GetInst()->CreateKey("JBMDebugRun", VK_SPACE);
	GameEngineInput::GetInst()->CreateKey("WMenuUI", 'P');
	GameEngineInput::GetInst()->CreateKey("BagOn", VK_LSHIFT);
	GameEngineInput::GetInst()->CreateKey("BagClose", VK_ESCAPE);

	WMenuUIRender_ = CreateRenderer("MenuUI2.bmp", 20);
	WMenuUIRender_->Off();
	WMenuArrowRender_ = CreateRenderer("MenuArrow2.bmp", 20);
	WMenuArrowRender_->SetPivot({ 240,-260 });
	WMenuArrowRender_->Off();

	FadeRender_ = CreateRenderer("FadeInOut.bmp", 10);
	FadeRender_->Off();
	FadeRightRender_ = CreateRenderer("FadeRight.bmp", 10);
	FadeRightRender_->Off();
	FadeLeftRender_ = CreateRenderer("FadeLeft.bmp", 10);
	FadeLeftRender_->Off();

	ShadowRender_ = CreateRenderer("shadow.bmp");
	ShadowRender_->SetPivot({ 0, 20 });
	ShadowRender_->Off();

	RedCollision_ = CreateCollision("RedColBox", { 60,60 });
	RedFrontCollision_ = CreateCollision("RedFrontColBox", { 20,5 }, { 0,-32 });

	RedRender_ = CreateRenderer();
	RedRender_->CreateAnimation("IdleUp.bmp", "IdleUp", 0, 0, 0.0f, false);
	RedRender_->CreateAnimation("IdleDown.bmp", "IdleDown", 0, 0, 0.0f, false);
	RedRender_->CreateAnimation("IdleLeft.bmp", "IdleLeft", 0, 0, 0.0f, false);
	RedRender_->CreateAnimation("IdleRight.bmp", "IdleRight", 0, 0, 0.0f, false);

	RedRender_->CreateAnimation("WalkUp.bmp", "WalkUp", 0, 2, 0.1f, true);
	RedRender_->CreateAnimation("WalkDown.bmp", "WalkDown", 0, 2, 0.1f, true);
	RedRender_->CreateAnimation("WalkLeft.bmp", "WalkLeft", 0, 2, 0.1f, true);
	RedRender_->CreateAnimation("WalkRight.bmp", "WalkRight", 0, 2, 0.1f, true);

	RedRender_->CreateAnimation("RunUp.bmp", "RunUp", 0, 2, 0.1f, true);
	RedRender_->CreateAnimation("RunDown.bmp", "RunDown", 0, 2, 0.1f, true);
	RedRender_->CreateAnimation("RunLeft.bmp", "RunLeft", 0, 2, 0.1f, true);
	RedRender_->CreateAnimation("RunRight.bmp", "RunRight", 0, 2, 0.1f, true);

	RedRender_->ChangeAnimation("IdleUp");
	RedRender_->SetPivot({ 0, -15 });

	BushActor_ = GetLevel()->CreateActor<Bush>();

	AnimationName_ = "Idle";
	ChangeDirText_ = "Up";
	CurrentDir_ = RedDir::Up;
	CurrentState_ = RedState::Idle;

	CurrentTileMap_ = RoomTileMap1::GetInst();
	SetPosition(CurrentTileMap_->GetWorldPostion(5, 4));	


	//UI
	InitMyPokemon();

	FadeActor_ = GetLevel()->CreateActor<FadeActor>();
	FadeActor_->SetPosition(GetPosition());


	//플레이어 아이템
	MyItemList_.push_back(PokemonInfoManager::GetInst().CreateItem("Potion"));
	MyItemList_.push_back(PokemonInfoManager::GetInst().CreateItem("Potion"));
	MyItemList_.push_back(PokemonInfoManager::GetInst().CreateItem("PokeBall"));
	MyItemList_.push_back(PokemonInfoManager::GetInst().CreateItem("PokeBall"));
}

void PlayerRed::Update()
{
	DirAnimationCheck();
	//Camera();
	StateUpdate();
	IsWMenuKey();
	WMenuUISelect();
	MoveAnim();
	FadeIn();
	FadeOut();
	FadeRL();
	Camera();
	UIUpdate();
	//Camera();
	InteractionUpdate();
	SoundTileCheck();

	if (true == GameEngineInput::GetInst()->IsPress("JBMTest"))
	{
		CurrentTileMap_ = WorldTileMap3::GetInst();
		SetPosition(CurrentTileMap_->GetWorldPostion(15, 45));
	}
	if (true == GameEngineInput::GetInst()->IsDown("JBMDebugRun"))
	{
		IsDebugRun_ = true;
		WorldMapSoundManager::GetInst()->PlayEffectSound(WorldSoundEffectEnum::Click);
	}
	if (true == GameEngineInput::GetInst()->IsUp("JBMDebugRun"))
	{
		IsDebugRun_ = false;
	}
}

void PlayerRed::Render()
{
	{
		char Text[30] = { 0 };
		sprintf_s(Text, "pos : %d , %d", CurrentTilePos_.ix(), CurrentTilePos_.iy());
		TextOut(GameEngine::BackBufferDC(),
			100,
			100,
			Text,
			static_cast<int>(strlen(Text)));
	}
}

void PlayerRed::PlayerSetMove(float4 _Value)
{
	if (false == CanMove())
	{
		return;
	}

	StartPos_ = GetPosition();
	float4 CheckPos = GetPosition() + _Value - CurrentTileMap_->GetPosition();
	TileIndex NextIndex = CurrentTileMap_->GetTileMap().GetTileIndex(CheckPos);

	switch (CurrentTileMap_->CanMove(NextIndex.X, NextIndex.Y, _Value))
	{
	case TileState::False:
		if (true == PlayerMoveTileCheck(NextIndex.X, NextIndex.Y))
		{
			Alpha_ = 0;
			IsFadeIn_ = true;
		}
		else
		{
			WorldMapSoundManager::GetInst()->PlayEffectSound(WorldSoundEffectEnum::Block);
		}
		break;
	case TileState::True:
		if (_Value.ix() == 0 && _Value.iy() > 0)
		{
			// 아래로 움직일때 수풀은 무조건 끄도록
			BushActor_->Off();
		}

		IsMove_ = true;
		IsBush_ = BushTileCheck(NextIndex.X, NextIndex.Y);
		IsBushEventReady_ = true;
		GoalPos_ = CurrentTileMap_->GetWorldPostion(NextIndex.X, NextIndex.Y);
		CurrentTilePos_ = { static_cast<float>(NextIndex.X), static_cast<float>(NextIndex.Y) };
		break;
	case TileState::MoreDown:
		IsJump_ = true;
		IsBush_ = BushTileCheck(NextIndex.X, NextIndex.Y + 1);
		IsBushEventReady_ = true;
		ShadowRender_->On();
		GoalPos_ = CurrentTileMap_->GetWorldPostion(NextIndex.X, NextIndex.Y + 1);
		CurrentTilePos_ = { static_cast<float>(NextIndex.X), static_cast<float>(NextIndex.Y) };

		if (true == IsDebugRun_)
		{
			NextMoveTime_ = GetAccTime() + 0.26f;
		}
		else
		{
			NextMoveTime_ = GetAccTime() + 0.51f;
		}
		break;
	default:
		break;
	}
}

void PlayerRed::Camera()
{
	CameraPos_.x = GetPosition().x - GameEngineWindow::GetInst().GetScale().Half().x;
	CameraPos_.y = GetPosition().y - GameEngineWindow::GetInst().GetScale().Half().y;
	GetLevel()->SetCameraPos(CameraPos_);

	/*
	if (0 > GetLevel()->GetCameraPos().x)
	{
		float4 CurrentCameraPos = GetLevel()->GetCameraPos();
		CurrentCameraPos.x = 0;
		GetLevel()->SetCameraPos(CurrentCameraPos);
	}
	if (0 > GetLevel()->GetCameraPos().y)
	{
		float4 CurrentCameraPos = GetLevel()->GetCameraPos();
		CurrentCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurrentCameraPos);
	}
	*/

	float WorldMapScaleX = 2938;
	float WorldMapScaleY = 7788;
	float CameraRectX = 960;
	float CameraRectY = 640;
	if (WorldMapScaleX <= GetLevel()->GetCameraPos().x + CameraRectX)
	{
		float4 CurrentCameraPos = GetLevel()->GetCameraPos();
		CurrentCameraPos.x = GetLevel()->GetCameraPos().x - (GetLevel()->GetCameraPos().x + CameraRectX - WorldMapScaleX);
		GetLevel()->SetCameraPos(CurrentCameraPos);
	}
	if (WorldMapScaleY <= GetLevel()->GetCameraPos().y + CameraRectY)
	{
		float4 CurrentCameraPos = GetLevel()->GetCameraPos();
		CurrentCameraPos.y = GetLevel()->GetCameraPos().y - (GetLevel()->GetCameraPos().y + CameraRectY - WorldMapScaleY);
		GetLevel()->SetCameraPos(CurrentCameraPos);
	}
}

GameEngineRenderer* Renderer_;
void PlayerRed::WMenuUISelect()
{
	if (false == WMenuUICheck_)
	{
		Renderer_ = CreateRenderer("WMenuUI_Dex.bmp");

		if (WMenuArrowRender_->GetPivot().y == -260 && true == GameEngineInput::GetInst()->IsDown("Up"))
		{
			Renderer_->SetOrder(100);
			WMenuArrowRender_->SetPivot({ 240,100 });
			return;
		}
		if (WMenuArrowRender_->GetPivot().y == -260 && true == GameEngineInput::GetInst()->IsDown("Down"))
		{
			WMenuArrowRender_->SetPivot({ 240,-200 });
			return;
		}

		if (WMenuArrowRender_->GetPivot().y == -200 && true == GameEngineInput::GetInst()->IsDown("Z"))
		{
			FadeActor_->SetPosition(GetPosition());
			FadeActor_->FadeOut();
			ChildUI_ = GetLevel()->CreateActor<PokemonMenu>(60, "PokemonMenu");
			ChildUI_->SetPosition(GetPosition() - GameEngineWindow::GetScale().Half());
			dynamic_cast<PokemonMenu*>(ChildUI_)->InitPokemonMenu();
			return;
		}
		if (WMenuArrowRender_->GetPivot().y == -200 && true == GameEngineInput::GetInst()->IsDown("Up"))
		{
			WMenuArrowRender_->SetPivot({ 240,-260 });
			return;
		}
		if (WMenuArrowRender_->GetPivot().y == -200 && true == GameEngineInput::GetInst()->IsDown("Down"))
		{
			WMenuArrowRender_->SetPivot({ 240,-140 });
			return;
		}

		if (WMenuArrowRender_->GetPivot().y == -140 && true == GameEngineInput::GetInst()->IsDown("Z"))
		{
			FadeActor_->SetPosition(GetPosition());
			FadeActor_->FadeOut();
			ChildUI_ = GetLevel()->CreateActor<Bag>(50);
			ChildUI_->SetPosition(GetPosition());
			dynamic_cast<Bag*>(ChildUI_)->BagInit();
			return;
		}
		if (WMenuArrowRender_->GetPivot().y == -140 && true == GameEngineInput::GetInst()->IsDown("Up"))
		{
			WMenuArrowRender_->SetPivot({ 240,-200 });
			return;
		}
		if (WMenuArrowRender_->GetPivot().y == -140 && true == GameEngineInput::GetInst()->IsDown("Down"))
		{
			WMenuArrowRender_->SetPivot({ 240,-80 });
			return;
		}

		if (WMenuArrowRender_->GetPivot().y == -80 && true == GameEngineInput::GetInst()->IsDown("Up"))
		{
			WMenuArrowRender_->SetPivot({ 240,-140 });
			return;
		}
		if (WMenuArrowRender_->GetPivot().y == -80 && true == GameEngineInput::GetInst()->IsDown("Down"))
		{
			WMenuArrowRender_->SetPivot({ 240,-20 });
			return;
		}

		if (WMenuArrowRender_->GetPivot().y == -20 && true == GameEngineInput::GetInst()->IsDown("Up"))
		{
			WMenuArrowRender_->SetPivot({ 240,-80 });
			return;
		}
		if (WMenuArrowRender_->GetPivot().y == -20 && true == GameEngineInput::GetInst()->IsDown("Down"))
		{
			WMenuArrowRender_->SetPivot({ 240,40 });
			return;
		}

		if (WMenuArrowRender_->GetPivot().y == 40 && true == GameEngineInput::GetInst()->IsDown("Up"))
		{
			WMenuArrowRender_->SetPivot({ 240,-20 });
			return;
		}
		if (WMenuArrowRender_->GetPivot().y == 40 && true == GameEngineInput::GetInst()->IsDown("Down"))
		{
			WMenuArrowRender_->SetPivot({ 240,100 });
			return;
		}

		if (WMenuArrowRender_->GetPivot().y == 100 && true == GameEngineInput::GetInst()->IsDown("Z"))
		{
			WMenuUIRender_->Off();
			WMenuArrowRender_->Off();
			WMenuUICheck_ = true;
			return;
		}
		if (WMenuArrowRender_->GetPivot().y == 100 && true == GameEngineInput::GetInst()->IsDown("Up"))
		{
			WMenuArrowRender_->SetPivot({ 240,40 });
			return;
		}
		if (WMenuArrowRender_->GetPivot().y == 100 && true == GameEngineInput::GetInst()->IsDown("Down"))
		{
			WMenuArrowRender_->SetPivot({ 240,-260 });
			return;
		}
	}
}

bool PlayerRed::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("Up") &&
		false == GameEngineInput::GetInst()->IsPress("Down") &&
		false == GameEngineInput::GetInst()->IsPress("Left") &&
		false == GameEngineInput::GetInst()->IsPress("Right"))
	{
		return false;
	}
	return true;
}

void PlayerRed::IsWMenuKey()
{
	if (true == GameEngineInput::GetInst()->IsDown("WMenuUI"))
	{
		if (true == WMenuUICheck_)
		{
			WorldMapSoundManager::GetInst()->PlayEffectSound(WorldSoundEffectEnum::Menu);
			ChangeState(RedState::Idle);
			WMenuUIRender_->On();
			WMenuArrowRender_->On();

			WMenuUICheck_ = false;
		}
		else if (false == WMenuUICheck_)
		{
			WMenuUIRender_->Off();
			WMenuArrowRender_->Off();

			WMenuUICheck_ = true;
		}
	}
}

void PlayerRed::MoveAnim()
{
	if (true == IsMove_)
	{
		if (true == IsDebugRun_)
		{
			LerpTime_ += GameEngineTime::GetDeltaTime() * 4.0f;
		}
		LerpTime_ += GameEngineTime::GetDeltaTime() * 4.0f;
		LerpX_ = GameEngineMath::LerpLimit(StartPos_.x, GoalPos_.x, LerpTime_);
		LerpY_ = GameEngineMath::LerpLimit(StartPos_.y, GoalPos_.y, LerpTime_);
		SetPosition({ LerpX_,LerpY_ });

		// 수풀
		if (LerpTime_ >= 0.8f && true == IsBushEventReady_)
		{
			IsBushEventReady_ = false;
			if (IsBush_)
			{
				BushActor_->On();
				BushActor_->SetPosition(GoalPos_);
				BushActor_->CreateEffect();
			}
			else
			{
				BushActor_->Off();
			}
		}

		if (LerpTime_ > 1.0f)
		{
			LerpTime_ = 0.0f;
			IsMove_ = false;
		}
	}
	if (true == IsJump_)
	{
		if (true == IsDebugRun_)
		{
			LerpTime_ += GameEngineTime::GetDeltaTime() * 2.0f;
		}
		LerpTime_ += GameEngineTime::GetDeltaTime() * 2.0f;
		LerpX_ = GameEngineMath::LerpLimit(StartPos_.x, GoalPos_.x, LerpTime_);
		LerpY_ = GameEngineMath::LerpLimit(StartPos_.y, GoalPos_.y, LerpTime_);
		SetPosition({ LerpX_,LerpY_ });

		// 높이조절
		if (LerpTime_ < 0.5f)
		{
			RedRender_->SetPivot({ 0, -15 - 32 * LerpTime_ * 2.0f });
		}
		else
		{
			RedRender_->SetPivot({ 0, -15 - 32 * (1 - ((LerpTime_ - 0.5f) * 2.0f)) });
		}

		// 수풀
		if (LerpTime_ >= 0.8f && true == IsBushEventReady_)
		{
			IsBushEventReady_ = false;
			if (IsBush_)
			{
				BushActor_->On();
				BushActor_->SetPosition(GoalPos_);
				BushActor_->CreateEffect();
			}
			else
			{
				BushActor_->Off();
			}
		}

		if (LerpTime_ > 1.0f)
		{
			LerpTime_ = 0.0f;
			IsJump_ = false;
			ShadowRender_->Off();
		}
	}
}

bool PlayerRed::CanMove()
{
	if (
		true == IsFadeIn_ ||
		true == IsInteraction_ ||
		ChildUI_ != nullptr ||
		false == WMenuUICheck_
		)
	{
		return false;
	}

	return true;
}

void PlayerRed::InteractionUpdate()
{
	if (true == IsFadeIn_ || true == IsInteraction_)
	{
		return;
	}

	// z키 누르면 잠깐 멈추듯 버벅거리는 현상, 눌리지 않았을 때만 return해서 그런 거 같음.
	//if (false == GameEngineInput::GetInst()->IsDown("Z"))
	//{
	//	return;
	//}

	float4 CheckPos = GetPosition() - CurrentTileMap_->GetPosition();
	TileIndex CheckIndex = CurrentTileMap_->GetTileMap().GetTileIndex(CheckPos);
	if (true == GameEngineInput::GetInst()->IsDown("Z"))
	{
		if (true == InteractTileCheck(CheckIndex.X, CheckIndex.Y, CurrentDir_))
		{
			IsInteraction_ = true;
		}
		if (true == InteractionNPC())
		{
			IsInteraction_ = true;
		}
	}
	else
	{
		{
			float4 NPCCheckPos = GetPosition() - WorldTileMap1::GetInst()->GetPosition();
			TileIndex NPCCheckIndex = WorldTileMap1::GetInst()->GetTileMap().GetTileIndex(NPCCheckPos);
			if (true == NPC5Check_)
			{
				ChangeDirText_ = "Down";
				RedRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
				PlayerSetMove(float4::DOWN * 50);

				if (19 == NPCCheckIndex.X && 16 == NPCCheckIndex.Y)
				{
					NPC5Check_ = false;
				}
			}
			else if (false == NPC5Check_ && 19 == NPCCheckIndex.X && 15 == NPCCheckIndex.Y)
			{
				IsInteraction_ = true;
				NPC5Check_ = true;

				InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
				TmpText->SetPosition(GetPosition());
				TmpText->AddText("I absolutely forbid you from");
				TmpText->AddText("going through here!");
				TmpText->AddText("This is private property!");
				TmpText->Setting();
			}
		}
		return;
	}
}

bool PlayerRed::InteractionNPC()
{
	std::vector<GameEngineCollision*> TmpVector;
	if (true == GameEngineInput::GetInst()->IsPress("Z") && RedCollision_->CollisionResult("NPC4DirZColBox", TmpVector))
	{
		//WMenuUICheck_ = false;
		for (size_t i = 0; i < TmpVector.size(); i++)
		{
			NPCBase* Newnpc = dynamic_cast<NPCBase*>(TmpVector[i]->GetActor());
			if (nullptr == Newnpc)
			{
				continue;
			}

			Newnpc->IsTalk_ = true;
		}

		InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
		TmpText->SetPosition(GetPosition());
		TmpText->AddText("Technology is incredible!");
		TmpText->AddText("");
		TmpText->AddText("You can now store and recall items");
		TmpText->AddText("and POKEMON as data via PC.");
		TmpText->Setting();

		return true;
	}
	return false;
}

void PlayerRed::UIUpdate()
{
	if (ChildUI_ != nullptr) // UI창이 뜰 경우
	{
		if (ChildUI_->IsUpdate() == false) //UI의 IsUpdate가 false면 해당 UI를 삭제시킵니다.
		{
			//FadeActor_->SetPosition(GetPosition());
			//FadeActor_->FadeOut();
			WMenuUICheck_ = true;

			ChildUI_->Death();
			ChildUI_ = nullptr;
		}
	}

	if (IsMove_ == true)
	{
		return;
	}

	if (ChildUI_ == nullptr)
	{
		if (true == GameEngineInput::GetInst()->IsDown("BagOn")) // 가방열기
		{
			FadeActor_->SetPosition(GetPosition());
			FadeActor_->FadeOut();
			ChildUI_ = GetLevel()->CreateActor<Bag>(50);
			ChildUI_->SetPosition(GetPosition());
			dynamic_cast<Bag*>(ChildUI_)->SetPlayerItemList(MyItemList_);
			dynamic_cast<Bag*>(ChildUI_)->BagInit();
		}

		if (true == GameEngineInput::GetInst()->IsDown("BagClose")) //포켓몬 메뉴 열기
		{
			FadeActor_->SetPosition(GetPosition());
			FadeActor_->FadeOut();
			ChildUI_ = GetLevel()->CreateActor<PokemonMenu>(60, "PokemonMenu");
			ChildUI_->SetPosition(GetPosition() - GameEngineWindow::GetScale().Half());
			dynamic_cast<PokemonMenu*>(ChildUI_)->InitPokemonMenu();
		}

		if (true == GameEngineInput::GetInst()->IsDown("C")) //메뉴UI 열기
		{
			WMenuUICheck_ = false;

			ChildUI_ = GetLevel()->CreateActor<MenuUI>(60, "MenuUI");
			ChildUI_->SetPosition(GetPosition() - GameEngineWindow::GetScale().Half());
			dynamic_cast<MenuUI*>(ChildUI_)->InitMenuUI();
		}
	}
}

void PlayerRed::InitMyPokemon()
{
	//

	Pokemon* Squirtle = PokemonInfoManager::GetInst().CreatePokemon("Squirtle");
	//Squirtle->GetInfo()->PlusHp(-70);
	//Squirtle->GetInfo()->SetMyLevel(4);
	//Squirtle->GetInfo()->SetMaxHp(170);

	MyPokemonList_.push_back(Squirtle);


}
