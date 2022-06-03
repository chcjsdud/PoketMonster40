#include "PlayerRed.h"

#include "RoomTileMap1.h"
#include "RoomTileMap2.h"
#include "RoomTileMap3.h"
#include "RoomTileMap4.h"
#include "RoomTileMap5.h"
#include "RoomTileMap6.h"
#include "RoomTileMap7.h"
#include "RoomTileMap8.h"
#include "WorldTileMap1.h"
#include "WorldTileMap2.h"
#include "WorldTileMap3.h"
#include "InteractionText.h"

bool PlayerRed::PlayerMoveTileCheck(int _X, int _Y)
{
	if (RoomTileMap1::GetInst() == CurrentTileMap_) // 레드집 2층
	{
		if (_X == 8 && _Y == 0)
		{
			NextTileMap_ = RoomTileMap2::GetInst();
			NextTilePos_ = { 9, 0 };
			return true;
		}
	}
	else if (RoomTileMap2::GetInst() == CurrentTileMap_) // 레드집 1층
	{
		if (_X == 10 && _Y == 0)
		{
			NextTileMap_ = RoomTileMap1::GetInst();
			NextTilePos_ = { 9,0 };
			return true;
		}

		if (_X == 3 && _Y == 7)
		{
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 15,92 };
			IsFadeRLCheck_ = true;
			return true;
		}
	}
	else if (RoomTileMap3::GetInst() == CurrentTileMap_) // 그린집
	{
		if (_X == 4 && _Y == 7)
		{
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 24,92 };
			IsFadeRLCheck_ = true;
			return true;
		}
	}
	else if (RoomTileMap4::GetInst() == CurrentTileMap_) // 오박사 연구소
	{
		if (_X == 6 && _Y == 11)
		{
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 25,98 };
			IsFadeRLCheck_ = true;
			return true;
		}
	}
	else if (RoomTileMap5::GetInst() == CurrentTileMap_) // 치료소
	{
		if (_X == 7 && _Y == 7)
		{
			if (BeforeTileMap_ == WorldTileMap1::GetInst())
			{
				NextTileMap_ = WorldTileMap1::GetInst();
				NextTilePos_ = { 23, 31 };
			}
			else if (BeforeTileMap_ == WorldTileMap3::GetInst())
			{
				NextTileMap_ = WorldTileMap3::GetInst();
				NextTilePos_ = { 18, 29 };
			}

			return true;
		}
	}
	else if (RoomTileMap6::GetInst() == CurrentTileMap_) // 상점
	{
		if (_X == 4 && _Y == 6)
		{
			if (BeforeTileMap_ == WorldTileMap1::GetInst())
			{
				NextTileMap_ = WorldTileMap1::GetInst();
				NextTilePos_ = { 33, 24 };
			}
			else if (BeforeTileMap_ == WorldTileMap3::GetInst())
			{
				NextTileMap_ = WorldTileMap3::GetInst();
				NextTilePos_ = { 29, 22 };
			}
			return true;
		}
	}
	else if (RoomTileMap7::GetInst() == CurrentTileMap_) // 학교
	{
		if (_X == 4 && _Y == 6)
		{
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 22, 23 };
			return true;
		}
	}
	else if (RoomTileMap8::GetInst() == CurrentTileMap_) // Npc 집
	{
		if (_X == 4 && _Y == 6)
		{
			NextTileMap_ = WorldTileMap1::GetInst();
			NextTilePos_ = { 22, 16 };
			return true;
		}
	}
	else if (WorldTileMap1::GetInst() == CurrentTileMap_)
	{
		if (_X == 15 && _Y == 91) // 레드 집
		{
			NextTileMap_ = RoomTileMap2::GetInst();
			NextTilePos_ = { 3,6 };
			return true;
		}
		if (_X == 24 && _Y == 91) // 그린 집
		{
			NextTileMap_ = RoomTileMap3::GetInst();
			NextTilePos_ = { 4,6 };
			return true;
		}
		if (_X == 25 && _Y == 97) // 오박사 연구소
		{
			NextTileMap_ = RoomTileMap4::GetInst();
			NextTilePos_ = { 6,10 };
			return true;
		}
		if (_X == 23 && _Y == 30) // 치료소
		{
			NextTileMap_ = RoomTileMap5::GetInst();
			NextTilePos_ = { 7, 6 };
			return true;
		}
		if (_X == 33 && _Y == 23) // 상점
		{
			NextTileMap_ = RoomTileMap6::GetInst();
			NextTilePos_ = { 4, 5 };
			return true;
		}
		if (_X == 22 && _Y == 22) // 학교
		{
			NextTileMap_ = RoomTileMap7::GetInst();
			NextTilePos_ = { 4, 5 };
			return true;
		}
		if (_X == 22 && _Y == 15) // Npc집
		{
			NextTileMap_ = RoomTileMap8::GetInst();
			NextTilePos_ = { 4, 5 };
			return true;
		}

		// 월드맵2로 타일 변경
		for (int y = 20; y <= 23; y++)
		{
			if (_X == -1 && _Y == y)
			{
				IsMove_ = true;
				BeforeTileMap_ = CurrentTileMap_;
				CurrentTileMap_ = WorldTileMap2::GetInst();
				GoalPos_ = CurrentTileMap_->GetWorldPostion(65, -4 + y);
				return false;
			}
		}

		// 월드맵3으로 타일 변경
		for (int x = 13; x <= 22; x++)
		{
			if (_X == x && _Y == -1)
			{
				IsMove_ = true;
				BeforeTileMap_ = CurrentTileMap_;
				CurrentTileMap_ = WorldTileMap3::GetInst();
				GoalPos_ = CurrentTileMap_->GetWorldPostion(4 + x, 118);
				return false;
			}
		}
	}
	else if (WorldTileMap2::GetInst() == CurrentTileMap_)
	{
		// 월드맵1로 타일 변경
		for (int y = 16; y <= 19; y++)
		{
			if (_X == 66 && _Y == y)
			{
				IsMove_ = true;
				BeforeTileMap_ = CurrentTileMap_;
				CurrentTileMap_ = WorldTileMap1::GetInst();
				GoalPos_ = CurrentTileMap_->GetWorldPostion(0, 4 + y);
				return false;
			}
		}
	}
	else if (WorldTileMap3::GetInst() == CurrentTileMap_)
	{
		// 월드맵1로 타일 변경
		for (int x = 17; x <= 26; x++)
		{
			if (_X == x && _Y == 119)
			{
				IsMove_ = true;
				BeforeTileMap_ = CurrentTileMap_;
				CurrentTileMap_ = WorldTileMap1::GetInst();
				GoalPos_ = CurrentTileMap_->GetWorldPostion(x - 4, 0);
				return false;
			}
		}

		// 월드맵4로 가야되는데 우선 위로 이동
		for (int x = 18; x <= 19; x++)
		{
			if (_X == x && _Y == 94)
			{
				NextTileMap_ = WorldTileMap3::GetInst();
				NextTilePos_ = { static_cast<float>(x), 56 };
				return true;
			}
		}

		// 월드맵4로 가야되는데 우선 아래로 이동
		for (int x = 18; x <= 19; x++)
		{
			if (_X == x && _Y == 57)
			{
				NextTileMap_ = WorldTileMap3::GetInst();
				NextTilePos_ = { static_cast<float>(x), 95 };
				return true;
			}
		}

		// 다른방 가야하는데 우선 위로 이동
		for (int x = 17; x <= 26; x++)
		{
			if (_X == x && _Y == 94)
			{
				IsMove_ = true;
				BeforeTileMap_ = CurrentTileMap_;
				CurrentTileMap_ = WorldTileMap1::GetInst();
				GoalPos_ = CurrentTileMap_->GetWorldPostion(x - 4, 0);
				return false;
			}
		}

		if (_X == 18 && _Y == 28) // 치료소
		{
			NextTileMap_ = RoomTileMap5::GetInst();
			NextTilePos_ = { 7, 6 };
			return true;
		}
		if (_X == 29 && _Y == 21) // 상점
		{
			NextTileMap_ = RoomTileMap6::GetInst();
			NextTilePos_ = { 4, 5 };
			return true;
		}
	}
	return false;
}

bool PlayerRed::InteractTileCheck(int _X, int _Y, RedDir _Dir)
{
	switch (_Dir)
	{
	case RedDir::Up:
		_Y -= 1;
		break;
	case RedDir::Down:
		_Y += 1;
		break;
	case RedDir::Left:
		_X -= 1;
		break;
	case RedDir::Right:
		_X += 1;
		break;
	default:
		break;
	}

	if (RoomTileMap1::GetInst() == CurrentTileMap_) // 레드집 2층
	{
		if (_X == 2 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("It's a nicely made dresser.");
			TmpText->AddText("It will hold a lot of stuff");
			TmpText->Setting();
			return true;
		}
		if (_X == 3 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("It's crammed full of POKEMON");
			TmpText->AddText("books");
			TmpText->Setting();
			return true;
		}
		if (_X == 4 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("It's crammed full of POKEMON");
			TmpText->AddText("books");
			TmpText->Setting();
			return true;
		}
		if (_X == 5 && _Y == 3)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Red Played with the NES.");
			TmpText->AddText(" ");
			TmpText->AddText("Okay!");
			TmpText->AddText("It's time to go!");
			TmpText->Setting();
			return true;
		}
	}
	else if (RoomTileMap2::GetInst() == CurrentTileMap_) // 레드집 1층
	{
		if (_X == 0 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("It smells delicious!");
			TmpText->AddText("Somebody's been cooking here.");
			TmpText->Setting();
			return true;
		}
		if (_X == 1 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("It smells delicious!");
			TmpText->AddText("Somebody's been cooking here.");
			TmpText->Setting();
			return true;
		}
		if (_X == 2 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Dishes and plates are neatly");
			TmpText->AddText("lined up.");
			TmpText->Setting();
			return true;
		}
		if (_X == 3 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Dishes and plates are neatly");
			TmpText->AddText("lined up.");
			TmpText->Setting();
			return true;
		}
		if (_X == 5 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("There's a movie on TV.");
			TmpText->AddText("Four boys are walking on railroad");
			TmpText->AddText("tracks.");
			TmpText->AddText(" ");
			TmpText->AddText("I better go, too.");
			TmpText->AddText(" ");
			TmpText->Setting();
			return true;
		}
	}
	else if (RoomTileMap3::GetInst() == CurrentTileMap_) // 그린집
	{
	}
	else if (RoomTileMap4::GetInst() == CurrentTileMap_) // 오박사 연구소
	{
		if (_X == 0 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Lights in different colors are");
			TmpText->AddText("flashing on and off.");
			TmpText->Setting();
			return true;
		}
		if (_X == 1 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Lights in different colors are");
			TmpText->AddText("flashing on and off.");
			TmpText->Setting();
			return true;
		}
		if (_X == 6 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Press P to open the Menu!");
			TmpText->Setting();
			return true;
		}
		if (_X == 7 && _Y == -1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("All POKEMON types have strong and");
			TmpText->AddText("weak points against others.");
			TmpText->Setting();
			return true;
		}
		for (int x = 9; x <= 12; x++)
		{
			if (_X == x && _Y == -1)
			{
				InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
				TmpText->SetPosition(GetPosition());
				TmpText->AddText("It's crammed full of POKEMON");
				TmpText->AddText("books.");
				TmpText->Setting();
				return true;
			}
		}
		for (int x = 0; x <= 4; x++)
		{
			if (_X == x && _Y == 6)
			{
				InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
				TmpText->SetPosition(GetPosition());
				TmpText->AddText("It's crammed full of POKEMON");
				TmpText->AddText("books.");
				TmpText->Setting();
				return true;
			}
		}
		for (int x = 8; x <= 12; x++)
		{
			if (_X == x && _Y == 6)
			{
				InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
				TmpText->SetPosition(GetPosition());
				TmpText->AddText("It's crammed full of POKEMON");
				TmpText->AddText("books.");
				TmpText->Setting();
				return true;
			}
		}

		for (int x = 1; x <= 2; x++)
		{
			for (int y = 1; y <= 3; y++)
			{
				if (_X == x && _Y == y)
				{
					InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
					TmpText->SetPosition(GetPosition());
					TmpText->AddText("What could this machine be?");
					TmpText->AddText("Better not mess around with it!");
					TmpText->Setting();
					return true;
				}
			}
		}
	}
	else if (RoomTileMap5::GetInst() == CurrentTileMap_) // 치료소
	{
		for (int x = 2; x <= 3; x++)
		{
			if (_X == x && _Y == -1)
			{
				InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
				TmpText->SetPosition(GetPosition());
				TmpText->AddText("It's crammed full of POKEMON");
				TmpText->AddText("books.");
				TmpText->Setting();
				return true;
			}
		}
		if (_X == 7 && _Y == 1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Welcome to our POKEMON CENTER!");
			TmpText->AddText("Would you like me to heal your");
			TmpText->AddText("POKEMON back to perfect health?");
			TmpText->Setting();
			return true;
		}
	}
	else if (RoomTileMap6::GetInst() == CurrentTileMap_) // 상점
	{
		if (_X == 4 && _Y == 6)
		{
			return true;
		}
		if (_X == 3 && _Y == 1)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Hi, there!");
			TmpText->AddText("May I help you?");
			TmpText->Setting();
			return true;
		}
	}
	else if (WorldTileMap1::GetInst() == CurrentTileMap_)
	{
		if (_X == 13 && _Y == 91)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("RED's house");
			TmpText->Setting();
			return true;
		}
		if (_X == 22 && _Y == 91)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("GREEN's house");
			TmpText->Setting();
			return true;
		}
		if (_X == 18 && _Y == 95)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("PALLET TOWN");
			TmpText->AddText("Shades of your journey await!");
			TmpText->Setting();
			return true;
		}
		if (_X == 14 && _Y == 98)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("TRAINER TIPS");
			TmpText->AddText(" ");
			TmpText->AddText("Press P to open the MENU!");
			TmpText->Setting();
			return true;
		}
		if (_X == 25 && _Y == 100)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("OAK POKEMON RESEARCH LAB");
			TmpText->Setting();
			return true;
		}
		if (_X == 18 && _Y == 75)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("ROUTE 1");
			TmpText->AddText("PALLET TOWN - VIRIDIAN CITY");
			TmpText->Setting();
			return true;
		}
		if (_X == 21 && _Y == 30)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Heal Your POKEMON!");
			TmpText->AddText("POKEMON CENTER");
			TmpText->Setting();
			return true;
		}
		if (_X == 22 && _Y == 30)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Heal Your POKEMON!");
			TmpText->AddText("POKEMON CENTER");
			TmpText->Setting();
			return true;
		}

		if (_X == 31 && _Y == 23)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("All your item needs fulfilled!");
			TmpText->AddText("POKEMON MART");
			TmpText->Setting();
			return true;
		}
		if (_X == 32 && _Y == 23)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("All your item needs fulfilled!");
			TmpText->AddText("POKEMON MART");
			TmpText->Setting();
			return true;
		}
		if (_X == 17 && _Y == 20)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("VIRIDIAN CITY");
			TmpText->AddText("The Eternally Green Paradise");
			TmpText->Setting();
			return true;
		}
		if (_X == 17 && _Y == 20)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("VIRIDIAN CITY");
			TmpText->AddText("The Eternally Green Paradise");
			TmpText->Setting();
			return true;
		}
		if (_X == 17 && _Y == 35)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("TRAINER TIPS");
			TmpText->AddText(" ");
			TmpText->AddText("The battle moves of POKEMON are");
			TmpText->AddText("limited by their POWER POINTS, PP.");
			TmpText->AddText("To replenish PP, rest your tired");
			TmpText->AddText("POKEMON at a POKEMON CENTER.");
			TmpText->Setting();
			return true;
		}

		if (_X == 20 && _Y == 5)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("TRAINER TIPS");
			TmpText->AddText(" ");
			TmpText->AddText("Catch POKEMON and expand your");
			TmpText->AddText("collection.");
			TmpText->AddText("The more you have, the easier it");
			TmpText->AddText("is to battle.");
			TmpText->Setting();
			return true;
		}
	}
	else if (WorldTileMap2::GetInst() == CurrentTileMap_)
	{
		if (_X == 22 && _Y == 23)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("POKEMON LEAGUE");
			TmpText->AddText("Front Gate");
			TmpText->Setting();
			return true;
		}
	}
	else if (WorldTileMap3::GetInst() == CurrentTileMap_)
	{
		if (_X == 20 && _Y == 116)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("ROUTE 2");
			TmpText->AddText("VIRIDIAN CITY - PEWTER CITY");
			TmpText->Setting();
			return true;
		}
		if (_X == 21 && _Y == 33)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("TRAINER TIPS");
			TmpText->AddText(" ");
			TmpText->AddText("All POKEMON that appear in battle,");
			TmpText->AddText("however briefly, earn EXP Points.");
			TmpText->Setting();
			return true;
		}
		if (_X == 16 && _Y == 28)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Heal Your POKEMON!");
			TmpText->AddText("POKEMON CENTER");
			TmpText->Setting();
			return true;
		}
		if (_X == 17 && _Y == 28)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("Heal Your POKEMON!");
			TmpText->AddText("POKEMON CENTER");
			TmpText->Setting();
			return true;
		}
		if (_X == 32 && _Y == 28)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("PEWTER CITY");
			TmpText->AddText("A Stone Gray City");
			TmpText->Setting();
			return true;
		}
		if (_X == 40 && _Y == 22)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("NOTICE!");
			TmpText->AddText("");
			TmpText->AddText("Thieves have been stealing POKEMON");
			TmpText->AddText("fossils from MT. MOON.");
			TmpText->AddText("Please call the PEWTER POLICE if");
			TmpText->AddText("you have any information.");
			TmpText->Setting();
			return true;
		}

		if (_X == 27 && _Y == 21)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("All your item needs fulfilled!");
			TmpText->AddText("POKEMON MART");
			TmpText->Setting();
			return true;
		}
		if (_X == 28 && _Y == 21)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("All your item needs fulfilled!");
			TmpText->AddText("POKEMON MART");
			TmpText->Setting();
			return true;
		}
		if (_X == 20 && _Y == 10)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("PEWTER MUSEUM OF SCIENCE");
			TmpText->Setting();
			return true;
		}

		if (_X == 12 && _Y == 19)
		{
			InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
			TmpText->SetPosition(GetPosition());
			TmpText->AddText("PEWTER CITY POKEMON GYM");
			TmpText->AddText("LEADER: BROCK");
			TmpText->AddText("The Rock-Solid POKEMON TRAINER!");
			TmpText->Setting();
			return true;
		}
	}
	return false;
}

bool PlayerRed::BushTileCheck(int _X, int _Y)
{
	if (WorldTileMap1::GetInst() == CurrentTileMap_)
	{
		{
			float4 LeftTop = { 21, 79 };
			float4 RightBot = { 22, 83 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}

		{
			float4 LeftTop = { 24, 78 };
			float4 RightBot = { 28, 79 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}

		{
			float4 LeftTop = { 26, 76 };
			float4 RightBot = { 30, 77 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}

		{
			float4 LeftTop = { 11, 78 };
			float4 RightBot = { 17, 79 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}

		{
			float4 LeftTop = { 13, 76 };
			float4 RightBot = { 19, 77 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}

		{
			float4 LeftTop = { 21, 68 };
			float4 RightBot = { 26, 72 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}

		{
			float4 LeftTop = { 25, 57 };
			float4 RightBot = { 30, 61 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}

		{
			float4 LeftTop = { 19, 50 };
			float4 RightBot = { 30, 54 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}
	}
	else if (WorldTileMap2::GetInst() == CurrentTileMap_)
	{
		{
			float4 LeftTop = { 49, 19 };
			float4 RightBot = { 54, 23 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}
		{
			float4 LeftTop = { 30, 19 };
			float4 RightBot = { 36, 23 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}
	}
	else if (WorldTileMap3::GetInst() == CurrentTileMap_)
	{
		{
			float4 LeftTop = { 19, 99 };
			float4 RightBot = { 25, 103 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}

		{
			float4 LeftTop = { 15, 45 };
			float4 RightBot = { 21, 51 };
			if (LeftTop.ix() <= _X && _X <= RightBot.ix())
			{
				if (LeftTop.iy() <= _Y && _Y <= RightBot.iy())
				{
					return true;
				}
			}
		}
	}

	return false;
}