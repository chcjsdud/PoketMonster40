#include "WorldTileMap3.h"
#include "Flower.h"

WorldTileMap3* WorldTileMap3::Inst_ = nullptr;

WorldTileMap3::WorldTileMap3() 
{
}

WorldTileMap3::~WorldTileMap3() 
{
}

void WorldTileMap3::Start()
{
	Inst_ = this;
	SetPosition({ 885 - 1650 + 36 , -9491 -3810 });
	TileMap_.TileRangeSetting(50, 119, { 64, 64 });
	ColMap_ = GameEngineImageManager::GetInst()->Find("ColMap3.bmp");
	//CreateRenderer("ColMap3.bmp", 100, RenderPivot::CENTER, {1650, 3810})->SetAlpha(100);

	for (int y = 50; y < 119; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			if (x % 2 == 0 && y % 2 != 0)
			{
				TileMap_.CreateTile<Tile>(x, y, "White.bmp", 1);
			}
			else if (x % 2 != 0 && y % 2 == 0)
			{
				TileMap_.CreateTile<Tile>(x, y, "White.bmp", 1);
			}
		}
	}

	MakeFlowers();
}

void WorldTileMap3::MakeFlowers()
{
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(33, 118));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(34, 117));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(33, 116));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(34, 110));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(29, 109));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(33, 109));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(30, 108));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(34, 108));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(29, 107));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(15, 104));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(15, 102));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(15, 100));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(15, 97));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(16, 96));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(14, 32));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(15, 33));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(16, 32));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(17, 33));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(7, 25));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(8, 24));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(8, 26));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(9, 25));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(10, 24));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(11, 25));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(12, 24));
	}

	for (int x = 28; x <= 31; x++)
	{
		{
			Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
			TmpFlower->SetPosition(GetWorldPostion(x, 31));
		}
		
		{
			Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
			TmpFlower->SetPosition(GetWorldPostion(x, 29));
		}
	}

	for (int x = 33; x <= 36; x++)
	{
		{
			Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
			TmpFlower->SetPosition(GetWorldPostion(x, 31));
		}

		{
			Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
			TmpFlower->SetPosition(GetWorldPostion(x, 29));
		}
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(29, 12));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(30, 11));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(31, 12));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(32, 11));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(30, 6));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(31, 5));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(32, 6));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(33, 5));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(10, 5));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(11, 6));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(12, 5));
	}
	{
		Flower* TmpFlower = GetLevel()->CreateActor<Flower>();
		TmpFlower->SetPosition(GetWorldPostion(12, 7));
	}
}