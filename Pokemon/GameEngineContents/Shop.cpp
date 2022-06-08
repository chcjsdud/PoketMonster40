#include "Shop.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

Shop::Shop()
	: ShopState_(ShopState::SelectDialog)
	, SalesList_(nullptr)
	, ShopDialog_(nullptr)
{
}

Shop::~Shop() 
{
}

void Shop::ShopInit()
{
	ShopState_ = ShopState::SelectDialog;

	SalesList_ = CreateRenderer("Shop_ItemList.bmp", -1, RenderPivot::LeftTop);
	ShopDialog_ = CreateRenderer("Shop_Dialog.bmp", -1, RenderPivot::LeftTop);
	CountDialog_ = CreateRenderer("Shop_Price.bmp", -1, RenderPivot::LeftTop);
	InBag_ = CreateRenderer("Shop_InBag.bmp", -1, RenderPivot::LeftTop);
	BuyDialog_ = CreateRenderer("Select_YesOrNO.bmp", -1, RenderPivot::LeftTop);
	Arrow_ = CreateRenderer("Bag_CurrentArrow.bmp", -1, RenderPivot::LeftTop);

	ShopDialog_->SetPivot(float4{ 25, 0 });
}

void Shop::ShopDestroy()
{
	SalesList_->Death();
	ShopDialog_->Death();
	InBag_->Death();
	CountDialog_->Death();
	BuyDialog_->Death();
	Arrow_->Death();
}

void Shop::OpenDialog()
{
	ShopDialog_->SetOrder(GetOrder());
}

void Shop::OpenSalesList()
{
	SalesList_->SetOrder(GetOrder() + 1);
}

void Shop::OpenCountDialog()
{
	InBag_->SetOrder(GetOrder() + 2);
	CountDialog_->SetOrder(GetOrder() + 2);
}

void Shop::OpenBuyDialog()
{
	BuyDialog_->SetOrder(GetOrder() + 3);
}

void Shop::AllClose()
{
	ShopDialog_->SetOrder(-1);
	SalesList_->SetOrder(-1);
	InBag_->SetOrder(-1);
	CountDialog_->SetOrder(-1);
	BuyDialog_->SetOrder(-1);
}

void Shop::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("SelectShop"))
	{
		GameEngineInput::GetInst()->CreateKey("SelectShop", 'z');
		GameEngineInput::GetInst()->CreateKey("Exitshop", 'x');
	}
}

void Shop::Update()
{
	switch (ShopState_)
	{
	case ShopState::SelectDialog:
		OpenDialog();

		if (true == GameEngineInput::GetInst()->IsDown("SelectShop"))
		{
			ShopState_ = ShopState::SelectSalesList;
			ShopDialog_->SetOrder(-1);
		}

		else if (true == GameEngineInput::GetInst()->IsDown("Exitshop"))
		{
			Off();
		}
		break;
	case ShopState::SelectSalesList:
		OpenSalesList();

		if (true == GameEngineInput::GetInst()->IsDown("SelectShop"))
		{
			ShopState_ = ShopState::SelectCount;
		}

		else if (true == GameEngineInput::GetInst()->IsDown("Exitshop"))
		{
			ShopState_ = ShopState::SelectDialog;
			SalesList_->SetOrder(-1);
		}
		break;


	case ShopState::SelectCount:
		OpenCountDialog();

		if (true == GameEngineInput::GetInst()->IsDown("SelectShop"))
		{
			ShopState_ = ShopState::SelectBuy;
		}

		else if (true == GameEngineInput::GetInst()->IsDown("Exitshop"))
		{
			ShopState_ = ShopState::SelectSalesList;
			InBag_->SetOrder(-1);
			CountDialog_->SetOrder(-1);
		}
		break;
	case ShopState::SelectBuy:
		OpenBuyDialog();

		if (true == GameEngineInput::GetInst()->IsDown("SelectShop"))
		{
			ShopState_ = ShopState::SelectSalesList;
			BuyDialog_->SetOrder(-1);
		}

		else if (true == GameEngineInput::GetInst()->IsDown("ExitShop"))
		{
			ShopState_ = ShopState::SelectCount;
			BuyDialog_->SetOrder(-1);
			InBag_->SetOrder(-1);
			CountDialog_->SetOrder(-1);
		}
		break;
	}
}



