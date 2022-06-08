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

	SalesList_ = CreateRenderer("Shop_ItemList.bmp", 0, RenderPivot::LeftTop);
	ShopDialog_ = CreateRenderer("Shop_Dialog.bmp", 0, RenderPivot::LeftTop);
	CountDialog_ = CreateRenderer("Shop_Price.bmp", 0, RenderPivot::LeftTop);
	InBag_ = CreateRenderer("Shop_InBag.bmp", 0, RenderPivot::LeftTop);
	BuyDialog_ = CreateRenderer("Select_YesOrNO.bmp", 0, RenderPivot::LeftTop);
	Arrow_ = CreateRenderer("Bag_CurrentArrow.bmp", 0, RenderPivot::LeftTop);

	ShopDialog_->SetPivot(float4{ 25, 0 });

	if (false == GameEngineInput::GetInst()->IsKey("Select"))
	{
		GameEngineInput::GetInst()->CreateKey("Select", 'z');
		GameEngineInput::GetInst()->CreateKey("Exit", 'x');
	}
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
	ShopDialog_->SetOrder(0);
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

void Shop::Start()
{
}

void Shop::Update()
{
	switch (ShopState_)
	{
	case ShopState::SelectDialog:
		OpenDialog();

		if (true == GameEngineInput::GetInst()->IsDown("Select"))
		{
			ShopState_ = ShopState::SelectSalesList;
		}

		if (true == GameEngineInput::GetInst()->IsDown("Exit"))
		{
			Off();
		}
		break;
	case ShopState::SelectSalesList:
		OpenSalesList();

		if (true == GameEngineInput::GetInst()->IsDown("Select"))
		{
			ShopState_ = ShopState::SelectCount;
		}
		break;
	case ShopState::SelectCount:
		OpenCountDialog();

		if (true == GameEngineInput::GetInst()->IsDown("Select"))
		{
			ShopState_ = ShopState::SelectBuy;
		}
		break;
	case ShopState::SelectBuy:
		OpenBuyDialog();

		if (true == GameEngineInput::GetInst()->IsDown("Select"))
		{
			ShopState_ = ShopState::SelectSalesList;
		}
		break;
	}
}



