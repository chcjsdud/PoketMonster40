#include "Shop.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "PlayerRed.h"
#include <string>
#include <GameEngineContentsCore/GameEngineContentFont.h>

Shop::Shop()
	: ShopState_(ShopState::SelectDialog)
	, SalesList_(nullptr)
	, ShopDialog_(nullptr)
	, CountDialog_(nullptr)
	, InBag_(nullptr)
	, BuyDialog_(nullptr)
	, Arrow_(nullptr)
	, BuyArrow_(nullptr)
	, ArrowIndex_(0)
	, ItemList_{}
	, KeyItemList_{}
	, BallList_{}
	, AllFontList_{}
	, CountList_{}
	, InBagCount_(nullptr)
	, ItemPreView_(nullptr)
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
	BuyArrow_ = CreateRenderer("Bag_CurrentArrow.bmp", -1, RenderPivot::LeftTop);

	ShopDialog_->SetPivot(float4{ 25, 0 });
	InBag_->SetPivot(float4{ 10, 330 });
	CountDialog_->SetPivot(float4{ 520, 260 });
	BuyDialog_->SetPivot(float4{ 530, 265 });

	ArrowIndex_ = 0;
	Arrow_->SetOrder(GetOrder() + 10);

	ItemPreView_ = CreateRenderer("PokeBall.bmp", - 1, RenderPivot::LeftTop);
	ItemPreView_->SetPivot(float4{ 45, 513 });
}

void Shop::ShopDestroy()
{
	SalesList_->Death();
	ShopDialog_->Death();
	InBag_->Death();
	CountDialog_->Death();
	BuyDialog_->Death();
	Arrow_->Death();
	BuyArrow_->Death();
	ItemPreView_->Death();

	DestroyAllFonts();
}


void Shop::OpenDialog()
{
	ShopDialog_->SetOrder(GetOrder());
}

void Shop::OpenSalesList()
{
	SalesList_->SetOrder(GetOrder() + 1);
	ItemPreView_->SetOrder(GetOrder() + 1);
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

void Shop::DestroyAllFonts()
{
	for (GameEngineContentFont* Font : AllFontList_)
	{
		if (nullptr != Font)
		{
			Font->Death();
		}
	}

	AllFontList_.clear();

	DestroyCountFont();
}

void Shop::DestroyCountFont()
{
	for (GameEngineContentFont* Font : CountList_)
	{
		if (nullptr != Font)
		{
			Font->Death();
		}
	}

	CountList_.clear();

}

void Shop::ArrowUpdate()
{
	static int Index_ = 1;

	if (ShopState_ != ShopState::SelectCount && true == GameEngineInput::GetInst()->IsDown("UpArrowShop"))
	{
		if (0 == ArrowIndex_)
		{
			return;
		}

		--ArrowIndex_;
	}

	else if (ShopState_ != ShopState::SelectCount && true == GameEngineInput::GetInst()->IsDown("DownArrowShop"))
	{
		++ArrowIndex_;
	}

	switch (ShopState_)
	{
	case ShopState::SelectDialog:
		switch (ArrowIndex_)
		{
		case 0:
			Arrow_->SetPivot(float4{ 50, 45 });
			break;

		case 1:
			Arrow_->SetPivot(float4{ 50, 110 });
			break;

		case 2:
			Arrow_->SetPivot(float4{ 50, 175 });
			break;

		default:
			ArrowIndex_ = 2;
			Arrow_->SetPivot(float4{ 50, 175 });
			break;
		}
		break;
	case ShopState::SelectSalesList:
		switch (ArrowIndex_)
		{
		case 0:				
			ItemPreView_->SetImage("PokeBall.bmp");
			ItemPreView_->SetPivot(float4{ 45, 513  });
			Arrow_->SetPivot(float4{ 355, 45 });
			break;

		case 1:
			ItemPreView_->SetImage("Potion.bmp");
			ItemPreView_->SetPivot(float4{ 50, 500 });
			Arrow_->SetPivot(float4{ 355, 110 });
			break;

		case 2:
			ItemPreView_->SetOrder(-1);
			Arrow_->SetPivot(float4{ 355, 175 });
			break;

		default:
			ArrowIndex_ = 2;
			Arrow_->SetPivot(float4{ 355, 175 });
			break;
		}
		break;

	case ShopState::SelectCount:
		if (true == GameEngineInput::GetInst()->IsDown("UpArrowShop"))
		{
			DestroyCountFont();

			++Index_;
			GameEngineContentFont* Count = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
			Count->SetPosition(GetPosition() + float4{ 580, 325 });
			Count->ShowString(std::to_string(Index_), true);
			CountList_.push_back(Count);
		}

		else if (true == GameEngineInput::GetInst()->IsDown("DownArrowShop"))
		{
			if (1 == Index_)
			{
				return;
			}

			DestroyCountFont();
			--Index_;

			GameEngineContentFont* Count = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
			Count->SetPosition(GetPosition() + float4{ 580, 325 });
			Count->ShowString(std::to_string(Index_), true);
			CountList_.push_back(Count);
		}
		break;

	case ShopState::SelectBuy:
		switch (ArrowIndex_)
		{
		case 0:
			BuyArrow_->SetOrder(GetOrder() + 10);
			BuyArrow_->SetPivot(float4{ 560, 310});
			break;

		case 1:
			BuyArrow_->SetOrder(GetOrder() + 10);
			BuyArrow_->SetPivot(float4{ 560, 365 });
			break;
		default:
			ArrowIndex_ = 2;
			BuyArrow_->SetPivot(float4{ 560, 365 });
			break;
		}
		break;
	}
}

void Shop::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("SelectShop"))
	{
		GameEngineInput::GetInst()->CreateKey("SelectShop", 'z');
		GameEngineInput::GetInst()->CreateKey("ExitShop", 'x');

		GameEngineInput::GetInst()->CreateKey("DownArrowShop", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("UpArrowShop", VK_UP);
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
			if (0 == ArrowIndex_)
			{
				ShopState_ = ShopState::SelectSalesList;
				ShopDialog_->SetOrder(-1);
				ArrowIndex_ = 0;

				GameEngineContentFont* Money = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
				Money->SetPosition(GetPosition() + float4{ 195, 85 });
				Money->ShowString(std::to_string(PlayerRed::MainRed_->GetMoney()), true);
				AllFontList_.push_back(Money);
			}

			else if (2 == ArrowIndex_)
			{
				ShopDestroy();
				Off();
			}
		}

		else if (true == GameEngineInput::GetInst()->IsDown("ExitShop"))
		{
			ShopDestroy();
			Off();
		}
		break;

	case ShopState::SelectSalesList:
		OpenSalesList();

		if (true == GameEngineInput::GetInst()->IsDown("SelectShop"))
		{
			ShopState_ = ShopState::SelectCount;

			int Index = 0;

			if (0 == ArrowIndex_)
			{
				for (Item* CurItem : ItemList_)
				{
					if (nullptr == CurItem)
					{
						continue;
					}

					if ("POTION" == CurItem->GetInfo()->GetNameConstPtr())
					{
						++Index;
					}
				}
			}

			else if (1 == ArrowIndex_)
			{
				for (Item* CurItem : ItemList_)
				{
					if (nullptr == CurItem)
					{
						continue;
					}

					if ("POKEBALL" == CurItem->GetInfo()->GetNameConstPtr())
					{
						++Index;
					}
				}
			}

			else if (2 == ArrowIndex_)
			{
				ShopState_ = ShopState::SelectDialog;
				DestroyAllFonts();
				SalesList_->SetOrder(-1);
				ItemPreView_->SetOrder(-10);

				ArrowIndex_ = 0;
				break;
			}

			InBagCount_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
			InBagCount_->SetPosition(GetPosition() + float4{ 270, 360 });
			InBagCount_->ShowString(std::to_string(Index), true);
			AllFontList_.push_back(InBagCount_);

			GameEngineContentFont* Count = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
			Count->SetPosition(GetPosition() + float4{ 580, 325 });
			Count->ShowString("1", true);
			CountList_.push_back(Count);
		}

		else if (true == GameEngineInput::GetInst()->IsDown("ExitShop"))
		{
			ShopState_ = ShopState::SelectDialog;
			DestroyAllFonts();
			SalesList_->SetOrder(-1);
			ItemPreView_->SetOrder(-10);

			ArrowIndex_ = 0;
		}
		break;


	case ShopState::SelectCount:
		OpenCountDialog();

		if (true == GameEngineInput::GetInst()->IsDown("SelectShop"))
		{
			ShopState_ = ShopState::SelectBuy;
			InBag_->SetOrder(-1);
			CountDialog_->SetOrder(-1);

			InBagCount_->Off();
			DestroyCountFont();

			ArrowIndex_ = 0;
		}

		else if (true == GameEngineInput::GetInst()->IsDown("ExitShop"))
		{
			ShopState_ = ShopState::SelectSalesList;
			InBag_->SetOrder(-1);
			CountDialog_->SetOrder(-1);

			InBagCount_->Off();
			DestroyCountFont();
		}
		break;
	case ShopState::SelectBuy:
		OpenBuyDialog();

		if (true == GameEngineInput::GetInst()->IsDown("SelectShop"))
		{
			ShopState_ = ShopState::SelectSalesList;
			BuyDialog_->SetOrder(-1);
			InBag_->SetOrder(-1);
			CountDialog_->SetOrder(-1);
			BuyArrow_->SetOrder(-1);
		}

		else if (true == GameEngineInput::GetInst()->IsDown("ExitShop"))
		{
			ShopState_ = ShopState::SelectCount;
			BuyDialog_->SetOrder(-1);
			InBag_->SetOrder(-1);
			CountDialog_->SetOrder(-1);
			BuyArrow_->SetOrder(-1);
		}
		break;
	}

	ArrowUpdate();
}



