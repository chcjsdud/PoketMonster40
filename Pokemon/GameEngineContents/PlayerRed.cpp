#include "PlayerRed.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

PlayerRed::PlayerRed() 
{
}

PlayerRed::~PlayerRed() 
{
}

void PlayerRed::Start()
{
	RedRender_ = CreateRenderer("IdleDown.bmp");
}

void PlayerRed::Update()
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

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 100);
	Camera();
}

void PlayerRed::Render()
{
}

void PlayerRed::Camera()
{
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
}
