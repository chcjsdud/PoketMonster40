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
	CreateRenderer("Battle_Back.bmp");
	SetPosition({ 480.0f, 225.0f });//이미지 위치 노가다 수작업..
}

void BattleBackground::Update()
{
}

void BattleBackground::Render()
{
}
