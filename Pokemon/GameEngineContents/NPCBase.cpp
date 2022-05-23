#include "NPCBase.h"
#include <GameEngineBase/GameEngineRandom.h>

NPCBase::NPCBase() 
	: NPCLerpTime_(0)
	, NPCNextMoveTime_(0)
	, NPCLerpX_(0)
	, NPCLerpY_(0)
	, IsMove_()
{
}

NPCBase::~NPCBase() 
{
}

void NPCBase::Start()
{
}

void NPCBase::Update()
{
	NPCMove();
	NPCMoveAnim();
}

void NPCBase::Render()
{
}

void NPCBase::NPCMove()
{
	if (nullptr == CurrentTileMap_)
	{
		return;
	}
	GameEngineRandom RandomValue_;
	int RandomStateNum_ = RandomValue_.RandomInt(0, 4);

	if (0 == RandomStateNum_)
	{
		State_ = NPCState::Idle;
	}
	else if (1 == RandomStateNum_)
	{
		State_ = NPCState::Up;
	}
	else if (2 == RandomStateNum_)
	{
		State_ = NPCState::Down;
	}
	else if (3 == RandomStateNum_)
	{
		State_ = NPCState::Left;
	}
	else if (4 == RandomStateNum_)
	{
		State_ = NPCState::Right;
	}
	
	switch (State_)
	{
	case NPCState::Idle:
		NPCMoveDir_ = float4::ZERO;
		break;
	case NPCState::Up:
		NPCMoveDir_ = float4::UP;
		break;
	case NPCState::Down:
		NPCMoveDir_ = float4::DOWN;
		break;
	case NPCState::Left:
		NPCMoveDir_ = float4::LEFT;
		break;
	case NPCState::Right:
		NPCMoveDir_ = float4::RIGHT;
		break;
	default:
		break;
	}

	if (GetAccTime() >= NPCNextMoveTime_)
	{
		NPCNextMoveTime_ = GetAccTime() + 0.26f;
		StartPos_ = GetPosition();
		float4 CheckPos_ = GetPosition() + (NPCMoveDir_ * 50) - CurrentTileMap_->GetPosition();
		TileIndex NextIndex = CurrentTileMap_->GetTileMap().GetTileIndex(CheckPos_);

		if (TileState::True == CurrentTileMap_->CanMove(NextIndex.X, NextIndex.Y, (NPCMoveDir_ * 50)))
		{
			IsMove_ = true;
			GoalPos_ = CurrentTileMap_->GetWorldPostion(NextIndex.X, NextIndex.Y);
			return;
		}
	}
}

void NPCBase::NPCMoveAnim()
{
	if (true == IsMove_)
	{
		NPCLerpTime_ += GameEngineTime::GetDeltaTime() * 4.0f;
		NPCLerpX_ = GameEngineMath::LerpLimit(StartPos_.x, GoalPos_.x, NPCLerpTime_);
		NPCLerpY_ = GameEngineMath::LerpLimit(StartPos_.y, GoalPos_.y, NPCLerpTime_);
		SetPosition({ NPCLerpX_,NPCLerpY_ });

		if (NPCLerpTime_ > 1.0f)
		{
			NPCLerpTime_ = 0.0f;
			IsMove_ = false;
		}
	}
}
