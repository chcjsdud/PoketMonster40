#include "Oak.h"
#include "PlayerRed.h"
#include "Green.h"
#include "RoomTileMap4.h"
#include "InteractionText.h"

void Oak::ShopEvent()
{
	if (false == PlayerRed::MainRed_->GetStartShopOakEvent())
	{
		return;
	}

	if (false == IsStartShop_[0])
	{
		IsStartShop_[0] = true;

		Green::NPCGreen->SetPosition(RoomTileMap4::GetInst()->GetWorldPostion(5, 10));
		Green::NPCGreen->NPCMoveDir(NPCDir::Up, 8);
	}

	if (false == IsStartShop_[1] && true == Green::NPCGreen->CanDirMoveTime())
	{
		IsStartShop_[1] = true;

		InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
		TmpText->SetPosition(GetPosition());
		TmpText->AddText("OAK: So, here are some tools for");
		TmpText->AddText("catching wild POKETMON.");
		TmpText->AddText("RED received five POKE BALLS.");
		TmpText->AddText("");
		TmpText->AddText("RED put the POKE BALLS");
		TmpText->AddText("in the POKE BALLS POCKET.");
		TmpText->AddText("When a wild POKEMON appears,");
		TmpText->AddText("it's fair game.");
		TmpText->AddText("Just throw a POKE BALL at it and");
		TmpText->AddText("try to catch it!");
		TmpText->AddText("Get moving, you two.");
		TmpText->AddText("");
		TmpText->AddText("This is a great undertaking in");
		TmpText->AddText("POKEMON history!");
		TmpText->AddText("GREEN: All right, Gramps!");
		TmpText->AddText("Leave it all to me!");
		TmpText->Setting();
	}

	if (true == IsStartShop_[2] && true == Green::NPCGreen->CanDirMoveTime())
	{
		IsStartShop_[2] = false;
		Green::NPCGreen->NPCMoveDir(NPCDir::Down, 8);
	}
}