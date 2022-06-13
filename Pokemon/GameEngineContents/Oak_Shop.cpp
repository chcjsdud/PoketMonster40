#include "Oak.h"
#include "PlayerRed.h"

void Oak::ShopEvent()
{
	if (false == PlayerRed::MainRed_->GetStartNPC5Event())
	{
		return;
	}


	if (false == IsStartShop_[0])
	{
		IsStartShop_[0] = true;
		NPCRender_->On();
		OakCurrentIndexX_ = static_cast<int>(PlayerRed::MainRed_->GetRedCurrentIndex().x - 2);
		OakCurrentIndexY_ = static_cast<int>(PlayerRed::MainRed_->GetRedCurrentIndex().y + 7);
		//CurrentTileMap_ = WorldTileMap1::GetInst();
		//SetPosition(WorldTileMap1::GetInst()->GetWorldPostion(OakCurrentIndexX_, OakCurrentIndexY_));
		NPCMoveDir(NPCDir::Up, 2);
	}
}