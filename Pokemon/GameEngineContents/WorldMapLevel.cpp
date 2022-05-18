#include "WorldMapLevel.h"
#include "WorldMapBackground.h"
#include "PlayerRed.h"
#include "WorldMapTileMap.h"
#include "WorldTileMap1.h"

WorldMapLevel::WorldMapLevel() 
{
}

WorldMapLevel::~WorldMapLevel() 
{
}

void WorldMapLevel::Loading()
{
	CreateActor<WorldMapBackground>();
	CreateActor<WorldTileMap1>();
	CreateActor<PlayerRed>();
}

void WorldMapLevel::Update()
{
}

