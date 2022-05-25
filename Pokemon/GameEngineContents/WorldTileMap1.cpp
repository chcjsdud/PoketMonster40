#include "WorldTileMap1.h"
#include "Flower.h"

WorldTileMap1* WorldTileMap1::Inst_ = nullptr;

WorldTileMap1::WorldTileMap1()
{
}

WorldTileMap1::~WorldTileMap1()
{
}

void WorldTileMap1::Start()
{
	Inst_ = this;
	SetPosition({ -474, -5689 });
	TileMap_.TileRangeSetting(70, 111, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("ColMap.bmp");

	//for (int y = 20; y < 80; y++)
	//{
	//	for (int x = 10; x < 40; x++)
	//	{
	//		if (x % 2 == 0 && y % 2 != 0)
	//		{
	//			TileMap_.CreateTile<Tile>(x, y, "White.bmp", 10);
	//		}
	//		else if (x % 2 != 0 && y % 2 == 0)
	//		{
	//			TileMap_.CreateTile<Tile>(x, y, "White.bmp", 10);
	//		}
	//	}
	//}

	MakeFlowers();
}

void WorldTileMap1::MakeFlowers()
{
	///// ²É 
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(14, 96));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(15, 96));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(16, 96));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(17, 96));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(14, 97));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(15, 97));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(16, 97));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(17, 97));
	}

	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(18, 79));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(19, 78));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(29, 79));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(30, 78));
	}

	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(11, 72));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(12, 71));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(13, 72));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(14, 71));
	}

	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(27, 63));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(28, 62));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(29, 63));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(30, 62));
	}

	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(12, 57));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(11, 56));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(12, 55));
	}

	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(11, 53));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(15, 53));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(12, 52));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(16, 52));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(11, 51));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(15, 51));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(12, 50));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(16, 50));
	}

	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(28, 46));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(30, 46));
	}

	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(25, 35));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(27, 35));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(29, 35));
	}

	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(33, 35));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(35, 35));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(37, 35));
	}

	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(31, 29));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(31, 27));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(32, 30));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(32, 28));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(33, 29));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(33, 27));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(34, 30));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(34, 28));
	}

	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(35, 18));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(36, 17));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(37, 18));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(38, 17));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(28, 0));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(30, 0));
	}
}