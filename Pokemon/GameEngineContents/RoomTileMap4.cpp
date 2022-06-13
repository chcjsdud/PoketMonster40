#include "RoomTileMap4.h"
#include "Room4Pokeball.h"

RoomTileMap4* RoomTileMap4::Inst_ = nullptr;

RoomTileMap4::RoomTileMap4()
{
}

RoomTileMap4::~RoomTileMap4()
{
}

void RoomTileMap4::Start()
{
	Inst_ = this;
	SetPosition({ -3916, 780 });
	TileMap_.TileRangeSetting(13, 11, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("Room4ColMap.bmp");

	Room4Pokeball* Pokeball0 = GetLevel()->CreateActor<Room4Pokeball>();
	Pokeball0->SetPosition(GetWorldPostion(8, 2));

	Room4Pokeball* Pokeball1 = GetLevel()->CreateActor<Room4Pokeball>();
	Pokeball1->SetPosition(GetWorldPostion(9, 2));

	Room4Pokeball* Pokeball2 = GetLevel()->CreateActor<Room4Pokeball>();
	Pokeball2->SetPosition(GetWorldPostion(10, 2));

	//for (int y = 0; y < 11; y++)
	//{
	//	for (int x = 0; x < 13; x++)
	//	{
	//		if (x % 2 == 0 && y % 2 != 0)
	//		{
	//			TileMap_.CreateTile<Tile>(x, y, "White.bmp", 1);
	//		}
	//		else if (x % 2 != 0 && y % 2 == 0)
	//		{
	//			TileMap_.CreateTile<Tile>(x, y, "White.bmp", 1);
	//		}
	//	}
	//}
}