#include "WorldMapLevel.h"
#include "WorldMapBackground.h"
#include "PlayerRed.h"
#include "NPC4.h"
#include "WorldTileMap1.h"
#include "WorldTileMap2.h"
#include "RoomTileMap1.h"
#include "RoomTileMap2.h"
#include "RoomTileMap3.h"
#include "RoomTileMap4.h"
#include "RoomTileMap5.h"
#include "RoomTileMap6.h"
#include "RoomTileMap7.h"
#include "RoomTileMap8.h"

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
	CreateActor<WorldTileMap2>();
	CreateActor<RoomTileMap1>();
	CreateActor<RoomTileMap2>();
	CreateActor<RoomTileMap3>();
	CreateActor<RoomTileMap4>();
	CreateActor<RoomTileMap5>();
	CreateActor<RoomTileMap6>();
	CreateActor<RoomTileMap7>();
	CreateActor<RoomTileMap8>();
	CreateActor<PlayerRed>();
	CreateActor<NPC4>();
}

void WorldMapLevel::Update()
{
}

