#include "PlayerRed.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
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

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 500);
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
