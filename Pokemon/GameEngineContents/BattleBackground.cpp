#include "BattleBackground.h"

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
	//SetPosition({ 480.0f, 225.0f });//이미지 위치 노가다 수작업..
	TextRender = CreateRenderer("Combat_TextFrame1.bmp", 0 ,RenderPivot::CENTER, {480.0f, 548.0f});
}

void BattleBackground::Update()
{
}

void BattleBackground::Render()
{
}
