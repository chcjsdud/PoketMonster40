#include "BattleLevel.h"
#include "BattleBackground.h"
#include "BattleInerface.h"

BattleLevel::BattleLevel()
{

}

BattleLevel::~BattleLevel()
{

}

void BattleLevel::Loading()
{
	CreateActor<BattleBackground>();
	

	BattleInerface* Interface = CreateActor<BattleInerface>(3);
	Interface->SetPosition({ 797.0f, 548.0f });
}

void BattleLevel::Update()
{
}

