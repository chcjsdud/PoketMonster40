#include "BattleLevel.h"
#include "BattleBackground.h"

BattleLevel::BattleLevel()
{

}

BattleLevel::~BattleLevel()
{

}

void BattleLevel::Loading()
{
	CreateActor<BattleBackground>();
}

void BattleLevel::Update()
{
}

