#include "BattleBackground.h"
#include <GameEngineBase/GameEngineTime.h>

BattleBackground::BattleBackground()
{

}

BattleBackground::~BattleBackground()
{

}

void BattleBackground::Start()
{
	//CreateRenderer("Battle_Back_NO_Ground.bmp");
	BackgroundRender = CreateRenderer("Battle_Back.bmp", 0, RenderPivot::CENTER, { 480.0f, 225.0f});
	TextRender = CreateRenderer("Combat_TextFrame1.bmp", 1 ,RenderPivot::CENTER, {480.0f, 548.0f});
	Fade_Up = CreateRenderer("FadeUp.bmp", 99, RenderPivot::CENTER, { 480.0f,320.0f });
	Fade_Down = CreateRenderer("FadeDown.bmp", 99, RenderPivot::CENTER, { 480.0f,320.0f });
}

void BattleBackground::Update()
{
	Fade_Time += GameEngineTime::GetDeltaTime()*200.0f;
	Fade_Up->SetPivot({ 480.0f ,320.0f - Fade_Time });
	if (Fade_Up->GetPivot().y < -640.0f)
	{	//일정 위치 이상 이동하면 꺼진다(안보여도 계속 이동중이니까..)
		Fade_Up->Off();
	}
	Fade_Down->SetPivot({ 480.0f ,320.0f + Fade_Time });
	if (Fade_Down->GetPivot().y > 640.0f)
	{	//일정 위치 이상 이동하면 꺼진다(안보여도 계속 이동중이니까..)
		Fade_Down->Off();
	}
}

void BattleBackground::Render()
{
}
