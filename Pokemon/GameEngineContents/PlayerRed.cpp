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
#include "RoomTileMap5.h"
#include "RoomTileMap6.h"
#include "WorldTileMap1.h"

#include "InteractionText.h"
#include "Flower.h"

PlayerRed* PlayerRed::MainRed_ = nullptr;

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
	, WMenuUICheck_(true)
	, LerpTime_(0)
	, FadeTime_(0)
	, Alpha_()
	, MyPokemonList_{}
	, MyItemList_{}
	, IsFadeIn_(false)
	, IsFadeOut_(false)
	, IsFadeRL_(false)
	, IsFadeRLCheck_(false)
	, LerpX_(0)
	, LerpY_(0)
	, MoveTimer_(0.0f)
	, NextMoveTime_(0.0f)
	, IsJump_(false)
	, IsMove_(false)
	, IsInteraction_(false)
	, NextTileMap_()
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
			//FadeRender_->Off();
			IsFadeIn_ = false;
			IsFadeOut_ = true;
			if (nullptr != NextTileMap_)
			{
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
		Alpha_ -= 1;

		FadeRender_->SetAlpha(Alpha_);

		if (0 >= Alpha_)
		{
			Alpha_ = 0;
			IsFadeOut_ = false;
		}
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
	WMenuArrowRender_->SetPivot({ 240,-260 });
	WMenuArrowRender_->Off();
	
	FadeRender_ = CreateRenderer("FadeInOut.bmp", 10);
	FadeRender_->Off();
	FadeRightRender_ = CreateRenderer("FadeRight.bmp", 10);
	FadeRightRender_->Off();
	FadeLeftRender_ = CreateRenderer("FadeLeft.bmp", 10);
	FadeLeftRender_->Off();
	
	ShadowRender_ = CreateRenderer("shadow.bmp");
	ShadowRender_->SetPivot({0, 20});
	ShadowRender_->Off();

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
	RedRender_->SetPivot({0, -15});

	AnimationName_ = "Idle";
	CurrentDir_ = RedDir::Up;
	CurrentState_ = RedState::Idle;

	CurrentTileMap_ = RoomTileMap1::GetInst();
	SetPosition(CurrentTileMap_->GetWorldPostion(5, 4));
	GetLevel()->CreateActor<Flower>()->SetPosition(GetPosition() + float4{64, 0});
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
	FadeRL();
	//Camera();
	InteractionUpdate();
}

void PlayerRed::Render()
{
}

void PlayerRed::PlayerSetMove(float4 _Value)
{
	if (true == IsFadeIn_ || true == IsInteraction_)
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
		break;
	case TileState::True:
		IsMove_ = true;
		GoalPos_ = CurrentTileMap_->GetWorldPostion(NextIndex.X, NextIndex.Y);
		break;
	case TileState::MoreDown:
		IsJump_ = true;
		ShadowRender_->On();
		NextMoveTime_ = GetAccTime() + 0.51f;
		GoalPos_ = CurrentTileMap_->GetWorldPostion(NextIndex.X, NextIndex.Y + 1);
		break;
	default:
		break;
	}
}

bool PlayerRed::PlayerMoveTileCheck(int _X, int _Y)
{
	if (RoomTileMap1::GetInst() == CurrentTileMap_) // 레드집 2층
	{
		if (_X == 8 && _Y == 0)
		{
			NextTileMap_ = RoomTileMap2::GetInst();
			NextTilePos_ = { 9, 0 };
			return true;
		}

		//if (_X == 8 && _Y == 0)
		//{
		//	NextTileMap_ = WorldTileMap1::GetInst();
		//	NextTilePos_ = { 23, 31 };
		//	return true;
		//}
	} 
	else if (RoomTileMap2::GetInst() == CurrentTileMap_) // 레드집 1층
	{
		if (_X == 10 && _Y == 0)
		{
			NextTileMap_ = RoomTileMap1::GetInst();
			NextTilePos_ = { 9,0 };
			return true;
		}

		if (_X == 3 && _Y == 7)
		{
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 15,92 };
			IsFadeRLCheck_ = true;
			return true;
		}
	}
	else if (RoomTileMap3::GetInst() == CurrentTileMap_) // 그린집
	{
		if (_X == 4 && _Y == 7)
		{
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 24,92 };
			IsFadeRLCheck_ = true;
			return true;
		}
	}
	else if (RoomTileMap4::GetInst() == CurrentTileMap_) // 오박사 연구소
	{
		if (_X == 6 && _Y == 11)
		{
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 25,98 };
			IsFadeRLCheck_ = true;
			return true;
		}
	}
	else if (RoomTileMap5::GetInst() == CurrentTileMap_) // 치료소
	{
		if (_X == 7 && _Y == 7)
		{
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 23, 31 };
			return true;
		}

		if (_X == 7 && _Y == 1)
		{
			// 치료 구현 및 추가필요
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 23, 31 };
			return true;
		}
	}
	else if (RoomTileMap6::GetInst() == CurrentTileMap_) // 상점
	{
		if (_X == 4 && _Y == 6)
		{
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 33, 24 };
			return true;
		}
		if (_X == 3 && _Y == 1)
		{
			// 상점 구현 및 추가필요
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 33, 24 };
			return true;
		}
	}
	else if (WorldTileMap1::GetInst() == CurrentTileMap_)
	{
		if (_X == 15 && _Y == 91) // 레드 집
		{
			NextTileMap_ = RoomTileMap2::GetInst();
			NextTilePos_ = { 3,6 };
			return true;
		}
		if (_X == 24 && _Y == 91) // 그린 집
		{
			NextTileMap_ = RoomTileMap3::GetInst();
			NextTilePos_ = { 4,6 };
			return true;
		}
		if (_X == 25 && _Y == 97) // 오박사 연구소
		{
			NextTileMap_ = RoomTileMap4::GetInst();
			NextTilePos_ = { 6,10 };
			return true;
		}
		if (_X == 23 && _Y == 30) // 치료소
		{
			NextTileMap_ = RoomTileMap5::GetInst();
			NextTilePos_ = { 7, 6 };
			return true;
		}
		if (_X == 33 && _Y == 23) // 상점
		{
			NextTileMap_ = RoomTileMap6::GetInst();
			NextTilePos_ = { 4, 5 };
			return true;
		}
	}
	return false;
}

void PlayerRed::MoveTile(PokemonTileMap& _Tile, float4 _Pos)
{
	CurrentTileMap_ = &_Tile;
	SetPosition(CurrentTileMap_->GetWorldPostion(_Pos.ix(), _Pos.iy()));
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

		if (WMenuArrowRender_->GetPivot().y == -200 && true == GameEngineInput::GetInst()->IsDown("Z"))
		{
			GameEngine::GetInst().ChangeLevel("UITestLevel");
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
			GameEngine::GetInst().ChangeLevel("BagTestLevel");
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
		LerpTime_ += GameEngineTime::GetDeltaTime() * 4.0f;
		LerpX_ = GameEngineMath::LerpLimit(StartPos_.x, GoalPos_.x, LerpTime_);
		LerpY_ = GameEngineMath::LerpLimit(StartPos_.y, GoalPos_.y, LerpTime_);
		SetPosition({ LerpX_,LerpY_ });

		if (LerpTime_ > 1.0f)
		{
			LerpTime_ = 0.0f;
			IsMove_ = false;
		}
	}
	if (true == IsJump_)
	{
		LerpTime_ += GameEngineTime::GetDeltaTime() * 2.0f;
		LerpX_ = GameEngineMath::LerpLimit(StartPos_.x, GoalPos_.x, LerpTime_);
		LerpY_ = GameEngineMath::LerpLimit(StartPos_.y, GoalPos_.y, LerpTime_);
		SetPosition({ LerpX_,LerpY_ });

		if (LerpTime_ > 1.0f)
		{
			LerpTime_ = 0.0f;
			IsJump_ = false;
			ShadowRender_->Off();
		}
	}
}

void PlayerRed::InteractionUpdate()
{
	if (true == IsFadeIn_ || true == IsInteraction_)
	{
		return;
	}

	if (false == GameEngineInput::GetInst()->IsDown("Z"))
	{
		return;
	}

	StartPos_ = GetPosition();
	float4 CheckPos = GetPosition() - CurrentTileMap_->GetPosition();
	TileIndex CheckIndex = CurrentTileMap_->GetTileMap().GetTileIndex(CheckPos);
	if (true == InteractTileCheck(CheckIndex.X, CheckIndex.Y, CurrentDir_))
	{
		IsInteraction_ = true;
	}
}

bool PlayerRed::InteractTileCheck(int _X, int _Y, RedDir _Dir)
{
	switch (_Dir)
	{
	case RedDir::Up:
		_Y -= 1;
		break;
	case RedDir::Down:
		_Y += 1;
		break;
	case RedDir::Left:
		_X -= 1;
		break;
	case RedDir::Right:
		_X += 1;
		break;
	default:
		break;
	}
	if (RoomTileMap1::GetInst() == CurrentTileMap_) // 레드집 2층
	{
		if (_X == 2 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("It's a nicely made dresser.");
			TmpText->AddText("It will hold a lot of stuff");
			TmpText->Setting();
			return true;
		}
		if (_X == 3 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("It's a nicely made dresser.");
			TmpText->AddText("It will hold a lot of stuff");
			TmpText->Setting();
			return true;
		}
		if (_X == 4 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("It's a nicely made dresser.");
			TmpText->AddText("It will hold a lot of stuff");
			TmpText->Setting();
			return true;
		}
		if (_X == 5 && _Y == 3)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Red Played with the NES.");
			TmpText->AddText("");
			TmpText->AddText(";Okay!");
			TmpText->AddText("It's time to go!");
			TmpText->Setting();
			return true;
		}
	}
	else if (RoomTileMap2::GetInst() == CurrentTileMap_) // 레드집 1층
	{
		if (_X == 0 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("It smells delicious!");
			TmpText->AddText("Somebody's been cooking here.");
			TmpText->Setting();
			return true;
		}
		if (_X == 1 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("It smells delicious!");
			TmpText->AddText("Somebody's been cooking here.");
			TmpText->Setting();
			return true;
		}
		if (_X == 2 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Dishes and plates are neatly");
			TmpText->AddText("lined up.");
			TmpText->Setting();
			return true;
		}
		if (_X == 3 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Dishes and plates are neatly");
			TmpText->AddText("lined up.");
			TmpText->Setting();
			return true;
		}
		if (_X == 5 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("There's a movie on TV.");
			TmpText->AddText("Four boys are walking on railroad");
			TmpText->AddText("tracks.");
			TmpText->AddText("");
			TmpText->AddText(";I better go, too.");
			TmpText->AddText("");
			TmpText->Setting();
			return true;
		}
	}
	else if (RoomTileMap3::GetInst() == CurrentTileMap_) // 그린집
	{
		if (_X == 4 && _Y == 7)
		{
			return true;
		}
	}
	else if (RoomTileMap4::GetInst() == CurrentTileMap_) // 오박사 연구소
	{
		if (_X == 6 && _Y == 11)
		{
			return true;
		}
	}
	else if (RoomTileMap5::GetInst() == CurrentTileMap_) // 치료소
	{
		if (_X == 7 && _Y == 7)
		{
			return true;
		}

		if (_X == 7 && _Y == 1)
		{
			return true;
		}
	}
	else if (RoomTileMap6::GetInst() == CurrentTileMap_) // 상점
	{
		if (_X == 4 && _Y == 6)
		{
			return true;
		}
		if (_X == 3 && _Y == 1)
		{
			return true;
		}
	}
	else if (WorldTileMap1::GetInst() == CurrentTileMap_)
	{
		if (_X == 15 && _Y == 91) // 레드 집 1층
		{
			return true;
		}
		if (_X == 24 && _Y == 91) // 그린 집
		{
			return true;
		}
		if (_X == 25 && _Y == 97) // 오박사 연구소
		{
			return true;
		}
		if (_X == 23 && _Y == 30) // 치료소
		{
			return true;
		}
		if (_X == 33 && _Y == 23) // 상점
		{
			return true;
		}
	}
	return false;
}
