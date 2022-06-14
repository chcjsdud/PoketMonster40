#include "Oak.h"
#include "PlayerRed.h"
#include "Green.h"
#include "RoomTileMap4.h"

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

		Green::NPCGreen->SetPosition(RoomTileMap4::GetInst()->GetWorldPostion(5, 10));
		Green::NPCGreen->NPCMoveDir(NPCDir::Up, 8);
	}
}