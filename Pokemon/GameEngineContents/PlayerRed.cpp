#include "PlayerRed.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

PlayerRed* PlayerRed::MainRed_ = nullptr;

PlayerRed::PlayerRed() 
{
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
}

void PlayerRed::Update()
{
	DirAnimationCheck();
	StateUpdate();
	
	Camera();
}

void PlayerRed::Render()
{
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
