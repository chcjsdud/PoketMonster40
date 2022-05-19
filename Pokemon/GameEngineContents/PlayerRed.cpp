#include "PlayerRed.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

#include "RoomTileMap1.h"
#include "RoomTileMap2.h"
#include "RoomTileMap3.h"
#include "RoomTileMap4.h"
#include "WorldTileMap1.h"

PlayerRed* PlayerRed::MainRed_ = nullptr;

PlayerRed::PlayerRed()
	: CurrentDir_()
	, CurrentState_()
	, CurrentTileMap_()
	, RedRender_()
	, AnimTimer_()
	, WMenuArrowRender_()
	, WMenuUIRender_()
	, WMenuUICheck_(true)
	, LerpTime_(0)
	, MyPokemonList_{nullptr}
	, MyItemList_{}
	, IsFadeIn_(false)
	, IsFadeOut_(false)
	, IsMoveCamera_(false)
{
	MyPokemonList_.resize(6);
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
	if (false == WMenuUICheck_)
	{
		return;
	}
	
	RedDir CheckDir_ = CurrentDir_;

	if (true == GameEngineInput::GetInst()->IsPress("Up"))
	{
		CheckDir_ = RedDir::Up;
		ChangeDirText_ = "Up";
	}
	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		CheckDir_ = RedDir::Down;
		ChangeDirText_ = "Down";
	}
	if (true == GameEngineInput::GetInst()->IsPress("Right"))
	{
		CheckDir_ = RedDir::Right;
		ChangeDirText_ = "Right";
	}
	if (true == GameEngineInput::GetInst()->IsPress("Left"))
	{
		CheckDir_ = RedDir::Left;
		ChangeDirText_ = "Left";
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
		Alpha_ += 2;

		FadeRender_->On();
		FadeRender_->SetAlpha(Alpha_);

		if (255 <= Alpha_)
		{
			Alpha_ = 255;
			FadeRender_->Off();
			IsFadeIn_ = false;
			IsMoveCamera_ = true;
		}
	}
}

void PlayerRed::FadeOut()
{
	if (true == IsFadeOut_)
	{
		Alpha_ -= 1;

		FadeRender_->On();
		FadeRender_->SetAlpha(Alpha_);

		if (0 >= Alpha_)
		{
			Alpha_ = 0;
			FadeRender_->SetAlpha(0);
			IsFadeOut_ = false;
		}
	}
}


void PlayerRed::Start()
{
	{
		GameEngineImage*
		Image = GameEngineImageManager::GetInst()->Find("IdleUp.bmp");
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

	GameEngineInput::GetInst()->CreateKey("WMenuUI", 'P');
	WMenuUIRender_ = CreateRenderer("MenuUI2.bmp",20);
	WMenuUIRender_->Off();
	WMenuArrowRender_ = CreateRenderer("MenuArrow2.bmp",20);
	WMenuArrowRender_->Off();
	
	FadeRender_ = CreateRenderer("FadeInOut.bmp", 10);
	FadeRender_->Off();
	
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

	RedRender_->ChangeAnimation("IdleDown");

	AnimationName_ = "Idle";
	CurrentDir_ = RedDir::Down;
	CurrentState_ = RedState::Idle;

	CurrentTileMap_ = RoomTileMap1::GetInst();
	SetPosition(CurrentTileMap_->GetWorldPostion(5, 4));
}

void PlayerRed::Update()
{
	DirAnimationCheck();
	Camera();
	StateUpdate();
	IsWMenuKey();
	WMenuUISelect();
	MoveAnim();
	FadeIn();
	FadeOut();
	//Camera();
}

void PlayerRed::Render()
{
}

void PlayerRed::PlayerSetMove(float4 _Value)
{
	LerpTime_ = 0;
	StartPos_ = GetPosition();
	float4 CheckPos = GetPosition() + _Value - CurrentTileMap_->GetPosition();
	TileIndex NextIndex = CurrentTileMap_->GetTileMap().GetTileIndex(CheckPos);

	if (CurrentTileMap_->CanMove(NextIndex.X, NextIndex.Y) == true)
	{
		IsMove_ = true;
		PlayerMoveTile(NextIndex.X, NextIndex.Y);
		GoalPos_ = CurrentTileMap_->GetWorldPostion(NextIndex.X, NextIndex.Y);
	}
}

void PlayerRed::PlayerMoveTile(int _X, int _Y)
{
	if (RoomTileMap1::GetInst() == CurrentTileMap_)
	{
		if (_X == 8 && _Y == 0)
		{
			IsFadeIn_ = true;
			Alpha_ = 0;
			CurrentTileMap_ = RoomTileMap2::GetInst();
			SetPosition(CurrentTileMap_->GetWorldPostion(9, 0));
			//MoveCamera(9, 0);
		}
	} 
	else if (RoomTileMap2::GetInst() == CurrentTileMap_)
	{
		if (_X == 9 && _Y == 0)
		{
			IsFadeIn_ = true;
			Alpha_ = 0;
			CurrentTileMap_ = RoomTileMap1::GetInst();
			SetPosition(CurrentTileMap_->GetWorldPostion(9, 0));
		}

		if (_X == 3 && _Y == 6)
		{
			CurrentTileMap_ = WorldTileMap1::GetInst();
			SetPosition(CurrentTileMap_->GetWorldPostion(15, 92));
		}
	}
	else if (RoomTileMap3::GetInst() == CurrentTileMap_)
	{
		if (_X == 4 && _Y == 6)
		{
			CurrentTileMap_ = WorldTileMap1::GetInst();
			SetPosition(CurrentTileMap_->GetWorldPostion(24, 92));
		}
	}
	else if (RoomTileMap4::GetInst() == CurrentTileMap_)
	{
		if (_X == 6 && _Y == 10)
		{
			CurrentTileMap_ = WorldTileMap1::GetInst();
			SetPosition(CurrentTileMap_->GetWorldPostion(25, 98));
		}
	}
	else if (WorldTileMap1::GetInst() == CurrentTileMap_)
	{
		if (_X == 15 && _Y == 92)
		{
			CurrentTileMap_ = RoomTileMap2::GetInst();
			SetPosition(CurrentTileMap_->GetWorldPostion(3, 6));
		}
		if (_X == 24 && _Y == 92)
		{
			CurrentTileMap_ = RoomTileMap3::GetInst();
			SetPosition(CurrentTileMap_->GetWorldPostion(4, 6));
		}
		if (_X == 25 && _Y == 98)
		{
			CurrentTileMap_ = RoomTileMap4::GetInst();
			SetPosition(CurrentTileMap_->GetWorldPostion(6, 10));
		}
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

void PlayerRed::MoveCamera(int _X, int _Y)
{
	if (true == IsMoveCamera_)
	{
		SetPosition(CurrentTileMap_->GetWorldPostion(_X, _Y));
	}
}

void PlayerRed::WMenuUISelect()
{
	if (false == WMenuUICheck_)
	{
		if (WMenuArrowRender_->GetPivot().y == -260 && true == GameEngineInput::GetInst()->IsDown("Up"))
		{
			WMenuArrowRender_->SetPivot({ 240,100 });
			return;
		}
		if (WMenuArrowRender_->GetPivot().y == -260 && true == GameEngineInput::GetInst()->IsDown("Down"))
		{
			WMenuArrowRender_->SetPivot({ 240,-200 });
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
			WMenuUIRender_->On();
			//-260, -200, -140, -80, -20, 40, 100
			WMenuArrowRender_->SetPivot({ 240,-260 });
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
	if (IsMove_ == false)
	{
		return;
	}

	LerpTime_ += GameEngineTime::GetDeltaTime();
	LerpX_ = GameEngineMath::LerpLimit(StartPos_.x, GoalPos_.x, LerpTime_ );
	LerpY_ = GameEngineMath::LerpLimit(StartPos_.y, GoalPos_.y, LerpTime_ );

	SetPosition({ LerpX_,LerpY_ });
}
