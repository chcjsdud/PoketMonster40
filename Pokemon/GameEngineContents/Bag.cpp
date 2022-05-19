#include "Bag.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "PokemonInfoManager.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include "Item.h"

Bag::Bag() 
	: BagType_(ItemType::ITEM)
	, BagRedrerer_(nullptr)
	, BagIndex_(0)
	, SelectIndex_(0)
{
}

Bag::~Bag() 
{
}

void Bag::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRenderer("Bag_Back.bmp");

	BagRedrerer_ = CreateRenderer("Bag_LeftOpen.bmp");
	BagRedrerer_->SetPivot({-317, -40});

	BagName_ = CreateRenderer("Bag_Items.bmp");
	BagName_->SetPivot({-314, -258 });

	LeftArrow_ = CreateRenderer("Bag_LeftArrow.bmp");
	LeftArrow_->SetPivot({-440, -25});
	LeftArrow_->SetOrder(-1);
	RightArrow_ = CreateRenderer("Bag_RightArrow.bmp");
	RightArrow_->SetPivot({ -200, -25 });
	UpArrow_ = CreateRenderer("Bag_UpArrow.bmp");
	UpArrow_->SetPivot({150, -290});
	UpArrow_->SetOrder(-1);
	DownArrow_ = CreateRenderer("Bag_DownArrow.bmp");
	DownArrow_->SetPivot({ 150, 90 });
	DownArrow_->SetOrder(-1);

	SelectArrow_ = CreateRenderer("Bag_CurrentArrow.bmp");
	SelectArrow_->SetPivot({-107, -260});

	ItemPreview_ = CreateRenderer("Bag_EnterArrow.bmp");
	ItemPreview_->SetPivot({-400, 225});

	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	BallList_.push_back(PokemonInfoManager::GetInst().FindItem("MonsterBall"));

	if (false == GameEngineInput::GetInst()->IsKey("LeftArrow"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftArrow", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("RightArrow", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("DownArrow", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("UpArrow", VK_UP);
	}

	ShowItemInfo();
}

void Bag::Update()
{
	MoveBag();
	MoveItem();

	if (true == IsMove_)
	{
		MoveTime_ += GameEngineTime::GetDeltaTime();

		if (0.1f <= MoveTime_)
		{
			IsMove_ = false;
			MoveTime_ = 0.f;

			ChangeBag();
		}
	}
}


void Bag::MoveBag()
{
	if (true == GameEngineInput::GetInst()->IsDown("LeftArrow"))
	{
		if (0 < BagIndex_)
		{
			IsMove_ = true;
			BagRedrerer_->PlusPivot({ 0, -15 });

			SelectIndex_ = 0;
			SelectArrow_->SetPivot({ -107, -260 });

			--BagIndex_;
			BagType_ = static_cast<ItemType>(BagIndex_);
		}
	}

	else if (true == GameEngineInput::GetInst()->IsDown("RightArrow"))
	{
		if (2 > BagIndex_)
		{
			IsMove_ = true;
			BagRedrerer_->PlusPivot({ 0, -15 });

			SelectIndex_ = 0;
			SelectArrow_->SetPivot({ -107, -260 });

			++BagIndex_;
			BagType_ = static_cast<ItemType>(BagIndex_);
		}
	}
}

void Bag::ChangeBag()
{
	switch (BagType_)
	{
	case ItemType::ITEM:
		BagRedrerer_->SetImage("Bag_LeftOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -40 });
		BagName_->SetImage("Bag_Items.bmp");

		LeftArrow_->SetOrder(-1);
		ShowItemInfo();
		break;
		
	case ItemType::KEYITEM:
		BagRedrerer_->SetImage("Bag_MiddleOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -48 });
		BagName_->SetImage("Bag_KeyItems.bmp");

		LeftArrow_->SetOrder(5);
		RightArrow_->SetOrder(5);
		ShowKeyItemInfo();
		break;

	case ItemType::BALL:
		BagRedrerer_->SetImage("Bag_RightOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -40 });
		BagName_->SetImage("Bag_PoketBalls.bmp");

		RightArrow_->SetOrder(-1);
		ShowBallInfo();
		break;
	}
}

void Bag::MoveItem()
{
	if (true == GameEngineInput::GetInst()->IsDown("DownArrow"))
	{
		switch (BagType_)
		{
		case ItemType::ITEM:
			if (ItemList_.size() > SelectIndex_)
			{
				++SelectIndex_;
				SelectArrow_->PlusPivot({0, 70});
			}
			break;
		case ItemType::KEYITEM:
			if (KeyItemList_.size() > SelectIndex_)
			{
				++SelectIndex_;
				SelectArrow_->PlusPivot({ 0, 70 });
			}
			break;
		case ItemType::BALL:
			if (BallList_.size() > SelectIndex_)
			{
				++SelectIndex_;
				SelectArrow_->PlusPivot({ 0, 70 });
			}
			break;
		}
	}

	else if (true == GameEngineInput::GetInst()->IsDown("UpArrow"))
	{
		switch (BagType_)
		{
		case ItemType::ITEM:
			if (0 < SelectIndex_)
			{
				--SelectIndex_;
				SelectArrow_->PlusPivot({ 0, -70 });
			}
			break;
		case ItemType::KEYITEM:
			if (0 < SelectIndex_)
			{
				--SelectIndex_;
				SelectArrow_->PlusPivot({ 0, -70 });
			}
			break;
		case ItemType::BALL:
			if (0 < SelectIndex_)
			{
				--SelectIndex_;
				SelectArrow_->PlusPivot({ 0, -70 });
			}
			break;
		}
	}
}


void Bag::ShowItemInfo()
{
	if (0 == ItemList_.size())
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");
		return;
	}

	ItemPreview_->SetImage(ItemList_[0]->GetNameCopy() + ".bmp");

	GameEngineContentFont* Fonts = GetLevel()->CreateActor<GameEngineContentFont>();
	Fonts->SetPosition({ -90, -260});
	Fonts->ShowString(ItemList_[0]->GetNameCopy(), true);
	AllFonts_.push_back(Fonts);
}

void Bag::ShowKeyItemInfo()
{
	if (0 == KeyItemList_.size())
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");
		return;
	}

	ItemPreview_->SetImage(KeyItemList_[0]->GetNameCopy() + ".bmp");
}

void Bag::ShowBallInfo()
{
	if (0 == BallList_.size())
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");
		return;
	}

	ItemPreview_->SetImage(BallList_[0]->GetNameCopy() + ".bmp");
}
