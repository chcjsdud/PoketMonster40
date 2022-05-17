#include "WorldMapLevel.h"
#include "WorldMapBackground.h"

WorldMapLevel::WorldMapLevel() 
{
}

WorldMapLevel::~WorldMapLevel() 
{
}

void WorldMapLevel::Loading()
{
	CreateActor<WorldMapBackground>();
}

void WorldMapLevel::Update()
{
}

