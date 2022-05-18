#include "WorldMapLevel.h"
#include "WorldMapBackground.h"
#include "PlayerRed.h"

WorldMapLevel::WorldMapLevel() 
{
}

WorldMapLevel::~WorldMapLevel() 
{
}

void WorldMapLevel::Loading()
{
	CreateActor<WorldMapBackground>();

	CreateActor<PlayerRed>();
}

void WorldMapLevel::Update()
{
}

