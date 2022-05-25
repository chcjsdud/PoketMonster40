#include "PlayerRed.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Bush.h"

void PlayerRed::IdleUpdate()
{
	if (false == WMenuUICheck_)
	{
		float4 MoveDir_ = float4::ZERO;
		return;
	}

	if (true == IsMoveKey())
	{
		ChangeState(RedState::Walk);
		return;
	}
}

void PlayerRed::WalkUpdate()
{
	if (false == WMenuUICheck_)
	{
		float4 MoveDir_ = float4::ZERO;
		return;
	}
	
	float4 MoveDir_ = float4::ZERO;
	if (true == GameEngineInput::GetInst()->IsPress("Up"))
	{
		MoveDir_ = float4::UP;
	}
	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		MoveDir_ = float4::DOWN;
	}
	if (true == GameEngineInput::GetInst()->IsPress("Left"))
	{
		MoveDir_ = float4::LEFT;
	}
	if (true == GameEngineInput::GetInst()->IsPress("Right"))
	{
		MoveDir_ = float4::RIGHT;
	}

	if (false == IsMoveKey())
	{
		ChangeState(RedState::Idle);
		return;
	}

	//SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 800);
	if (GetAccTime() >= NextMoveTime_)
	{
		NextMoveTime_ = GetAccTime() + 0.26f;
		PlayerSetMove(MoveDir_ * 50);
	}
}

void PlayerRed::RunUpdate()
{
	float4 MoveDir_ = float4::ZERO;
	if (true == GameEngineInput::GetInst()->IsPress("Up"))
	{
		MoveDir_ = float4::UP;
	}
	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		MoveDir_ = float4::DOWN;
	}
	if (true == GameEngineInput::GetInst()->IsPress("Left"))
	{
		MoveDir_ = float4::LEFT;
	}
	if (true == GameEngineInput::GetInst()->IsPress("Right"))
	{
		MoveDir_ = float4::RIGHT;
	}

	if (false == IsMoveKey())
	{
		ChangeState(RedState::Idle);
		return;
	}

	//SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 800);
	//PlayerSetMove(MoveDir_ * 32);
}

void PlayerRed::IdleStart()
{
	AnimationName_ = "Idle";
	RedRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void PlayerRed::WalkStart()
{
	AnimationName_ = "Walk";
	RedRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void PlayerRed::RunStart()
{
	AnimationName_ = "Run";
	RedRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}