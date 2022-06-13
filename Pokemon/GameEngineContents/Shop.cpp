#include "Shop.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "PlayerRed.h"
#include <string>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include "PokemonInfoManager.h"


//상점 초반이 이미 만들어져있음
Shop::Shop()
	: ShopState_(ShopState::SelectSalesList)
	, SalesList_(nullptr)
	, CountDialog_(nullptr)
	, InBag_(nullptr)
	, BuyDialog_(nullptr)
	, Arrow_(nullptr)
	, BuyArrow_(nullptr)
	, ArrowIndex_(0)
	, BuyArrowIndex_(0)
	, ItemList_{}
	, KeyItemList_{}
	, BallList_{}
	, AllFontList_{}
	, CountFontList_{}
	, InBagCount_(nullptr)
	, Money_(nullptr)
	, PriceFont_(nullptr)
	, Price_(0)
	, ItemCount_(0)
	, ItemPreView_(nullptr)
	, InputTime_(0.f)
{
}

Shop::~Shop() 
{
}

void Shop::ShopInit()
{
	ShopState_ = ShopState::SelectSalesList;

	SalesList_ = CreateRenderer("Shop_ItemList.bmp", -1, RenderPivot::LeftTop);
	CountDialog_ = CreateRenderer("Shop_Price.bmp", -1, RenderPivot::LeftTop);
	InBag_ = CreateRenderer("Shop_InBag.bmp", -1, RenderPivot::LeftTop);
	BuyDialog_ = CreateRenderer("Select_YesOrNO.bmp", -1, RenderPivot::LeftTop);
	Arrow_ = CreateRenderer("Bag_CurrentArrow.bmp", -1, RenderPivot::LeftTop);
	BuyArrow_ = CreateRenderer("Bag_CurrentArrow.bmp", -1, RenderPivot::LeftTop);

	InBag_->SetPivot(float4{ 10, 330 });
	CountDialog_->SetPivot(float4{ 520, 260 });
	BuyDialog_->SetPivot(float4{ 530, 265 });

	ArrowIndex_ = 0;
	Arrow_->SetPivot(float4{ 355, 45 });

	ItemPreView_ = CreateRenderer("PokeBall_ShopUI.bmp", - 1, RenderPivot::LeftTop);
	ItemPreView_->SetPivot(float4{ 0, 465 });

	Money_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
	Money_->SetPosition(GetPosition() + float4{ 195, 80 });
	Money_->ShowString(std::to_string(PlayerRed::MainRed_->GetMoney()), true);
	MoneyFontList_.push_back(Money_);

	Money_->Off();
}

void Shop::ShopDestroy()
{
	SalesList_->Death();
	InBag_->Death();
	CountDialog_->Death();
	BuyDialog_->Death();
	Arrow_->Death();
	BuyArrow_->Death();
	ItemPreView_->Death();
	Money_->Death();

	DestroyAllFonts();
}


void Shop::OpenSalesList()
{
	SalesList_->SetOrder(GetOrder() + 1);
	ItemPreView_->SetOrder(GetOrder() + 1);
	Arrow_->SetOrder(GetOrder() + 10);
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
	DestroyInBagFont();
	DestroyMoneyFont();
	DestroyPriceFont();
}

void Shop::DestroyCountFont()
{
	for (GameEngineContentFont* Font : CountFontList_)
	{
		if (nullptr != Font)
		{
			Font->Death();
		}
	}

	CountFontList_.clear();
}

void Shop::DestroyMoneyFont()
{
	for (GameEngineContentFont* Font : MoneyFontList_)
	{
		if (nullptr != Font)
		{
			Font->Death();
		}
	}

	MoneyFontList_.clear();
}

void Shop::DestroyInBagFont()
{
	for (GameEngineContentFont* Font : InBagFontList_)
	{
		if (nullptr != Font)
		{
			Font->Death();
		}
	}

	InBagFontList_.clear();
}

void Shop::DestroyPriceFont()
{
	for (GameEngineContentFont* Font : PriceFontList_)
	{
		if (nullptr != Font)
		{
			Font->Death();
		}
	}

	PriceFontList_.clear();
}

void Shop::ArrowUpdate()
{
	if (ShopState_ != ShopState::SelectCount && true == GameEngineInput::GetInst()->IsDown("UpArrowShop"))
	{
		if (ShopState_ == ShopState::SelectBuy)
		{
			if (0 == BuyArrowIndex_)
			{
				return;
			}

			++BuyArrowIndex_;
			return;
		}

		if (0 == ArrowIndex_)
		{
			return;
		}

		--ArrowIndex_;
	}

	else if (ShopState_ != ShopState::SelectCount && true == GameEngineInput::GetInst()->IsDown("DownArrowShop"))
	{
		if (ShopState_ == ShopState::SelectBuy)
		{
			--BuyArrowIndex_;
			return;
		}

		++ArrowIndex_;
	}

	switch (ShopState_)
	{
	case ShopState::SelectSalesList:
		switch (ArrowIndex_)
		{
		case 0:				
			ItemPreView_->SetImage("PokeBall_ShopUI.bmp");
			Arrow_->SetPivot(float4{ 355, 45 });
			break;

		case 1:
			ItemPreView_->SetImage("Potion_ShopUI.bmp");
			Arrow_->SetPivot(float4{ 355, 110 });
			break;

		case 2:
			ItemPreView_->SetImage("Close_ShopUI.bmp");
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

			++ItemCount_;

			if (0 == ArrowIndex_)
			{
				Price_ += 200;

				DestroyPriceFont();

				PriceFont_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
				PriceFont_->SetPosition(GetPosition() + float4{ 720, 330 });
				PriceFont_->ShowString(std::to_string(Price_), true);
				PriceFontList_.push_back(PriceFont_);
			}

			else if (1 == ArrowIndex_)
			{
				Price_ += 300;

				DestroyPriceFont();

				PriceFont_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
				PriceFont_->SetPosition(GetPosition() + float4{ 720, 330 });
				PriceFont_->ShowString(std::to_string(Price_), true);
				PriceFontList_.push_back(PriceFont_);
			}

			GameEngineContentFont* Count = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
			Count->SetPosition(GetPosition() + float4{ 580, 325 });
			Count->ShowString(std::to_string(ItemCount_), true);
			CountFontList_.push_back(Count);
		}

		else if (true == GameEngineInput::GetInst()->IsDown("DownArrowShop"))
		{
			if (1 == ItemCount_)
			{
				ItemCount_ = 1;
				return;
			}

			DestroyCountFont();

			--ItemCount_;

			if (0 == ArrowIndex_)
			{
				Price_ -= 200;

				DestroyPriceFont();

				PriceFont_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
				PriceFont_->SetPosition(GetPosition() + float4{ 720, 330 });
				PriceFont_->ShowString(std::to_string(Price_), true);
				PriceFontList_.push_back(PriceFont_);
			}

			else if (1 == ArrowIndex_)
			{
				Price_ -= 300;

				DestroyPriceFont();

				PriceFont_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
				PriceFont_->SetPosition(GetPosition() + float4{ 720, 330 });
				PriceFont_->ShowString(std::to_string(Price_), true);
				PriceFontList_.push_back(PriceFont_);
			}

			GameEngineContentFont* Count = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
			Count->SetPosition(GetPosition() + float4{ 580, 325 });
			Count->ShowString(std::to_string(ItemCount_), true);
			CountFontList_.push_back(Count);
		}
		break;

	case ShopState::SelectBuy:
		switch (BuyArrowIndex_)
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
			BuyArrowIndex_ = 2;
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
	if (InputTime_ < 0.1f)
	{
		InputTime_ += GameEngineTime::GetDeltaTime();
		return;
	}

	switch (ShopState_)
	{
	case ShopState::SelectSalesList:
		OpenSalesList();

		if (false == Money_->IsUpdate())
		{
			DestroyMoneyFont();

			Money_->On();
			Money_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
			Money_->SetPosition(GetPosition() + float4{ 195, 80 });
			Money_->ShowString(std::to_string(PlayerRed::MainRed_->GetMoney()), true);
			MoneyFontList_.push_back(Money_);
		}

		if (true == GameEngineInput::GetInst()->IsDown("SelectShop"))
		{
			ShopState_ = ShopState::SelectCount;

			int Index = 0;

			if (0 == ArrowIndex_)
			{
				for (Item* CurItem : BallList_)
				{
					if ("POKEBALL" == CurItem->GetInfo()->GetNameCopy())
					{
						++Index;
					}
				}

				DestroyPriceFont();

				PriceFont_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
				PriceFont_->SetPosition(GetPosition() + float4{ 720, 330 });
				PriceFont_->ShowString(std::to_string(200), true);
				PriceFontList_.push_back(PriceFont_);
			}

			else if (1 == ArrowIndex_)
			{
				for (Item* CurItem : ItemList_)
				{
					if ("POTION" == CurItem->GetInfo()->GetNameCopy())
					{
						++Index;
					}
				}

				DestroyPriceFont();

				PriceFont_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
				PriceFont_->SetPosition(GetPosition() + float4{ 720, 330 });
				PriceFont_->ShowString(std::to_string(300), true);
				PriceFontList_.push_back(PriceFont_);
			}

			else if (2 == ArrowIndex_)
			{
				ShopDestroy();
				Off();
				break;
			}

			InBagCount_ = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
			InBagCount_->SetPosition(GetPosition() + float4{ 270, 360 });
			InBagCount_->ShowString(std::to_string(Index), true);
			InBagFontList_.push_back(InBagCount_);

			GameEngineContentFont* Count = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder() + 10);
			Count->SetPosition(GetPosition() + float4{ 580, 325 });
			Count->ShowString("1", true);
			CountFontList_.push_back(Count);
		}

		else if (true == GameEngineInput::GetInst()->IsDown("ExitShop"))
		{
			ShopDestroy();
			Off();
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
			DestroyInBagFont();
			DestroyCountFont();
			DestroyPriceFont();
		}

		else if (true == GameEngineInput::GetInst()->IsDown("ExitShop"))
		{
			ShopState_ = ShopState::SelectSalesList;
			InBag_->SetOrder(-1);
			CountDialog_->SetOrder(-1);

			InBagCount_->Off();
			DestroyInBagFont();
			DestroyCountFont();
			DestroyPriceFont();

			ItemCount_ = 0;
			Price_ = 0;
		}
		break;
	case ShopState::SelectBuy:
		OpenBuyDialog();

		if (true == GameEngineInput::GetInst()->IsDown("SelectShop"))
		{
			//계산
			int Money = PlayerRed::MainRed_->GetMoney();
			PlayerRed::MainRed_->SetMoney(Money - Price_);

			if (0 == ArrowIndex_)
			{
				int Index = Price_ / 200;

				for (size_t i = 0; i < Index; i++)
				{
					PlayerRed::MainRed_->GetItemList().push_back(PokemonInfoManager::GetInst().CreateItem("POKEBALL"));
				}
			}

			else if (1 == ArrowIndex_)
			{
				int Index = Price_ / 300;

				for (size_t i = 0; i < Index; i++)
				{
					PlayerRed::MainRed_->GetItemList().push_back(PokemonInfoManager::GetInst().CreateItem("POTION"));
				}
			}

			ShopState_ = ShopState::SelectSalesList;
			BuyArrowIndex_ = 0;

			BuyDialog_->SetOrder(-1);
			InBag_->SetOrder(-1);
			CountDialog_->SetOrder(-1);
			BuyArrow_->SetOrder(-1);

			Price_ = 0;
			ItemCount_ = 0;
			Money_->Off();
		}

		else if (true == GameEngineInput::GetInst()->IsDown("ExitShop"))
		{
			ShopState_ = ShopState::SelectSalesList;
			BuyArrowIndex_ = 0;

			BuyDialog_->SetOrder(-1);
			InBag_->SetOrder(-1);
			CountDialog_->SetOrder(-1);
			BuyArrow_->SetOrder(-1);
		
			Money_->Off();
		}
		break;
	}

	ArrowUpdate();
}



