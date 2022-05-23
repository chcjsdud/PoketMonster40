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
	, BagName_(nullptr)
	, LeftArrow_(nullptr)
	, RightArrow_(nullptr)
	, UpArrow_(nullptr)
	, DownArrow_(nullptr)
	, SelectArrow_(nullptr)
	, SelectIndex_(0)
	, ItemPreview_(nullptr)
	, AllFonts_{nullptr}
	, BagIndex_(0)
	, BagMoveTime_(0.f)
	, IsMove_(false)
	, ArrowMoveTime_(0.f)
	, IsArrowSync_(false)
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
	LeftArrow_->SetPivot({-436, -25});
	LeftArrow_->SetOrder(-1);
	RightArrow_ = CreateRenderer("Bag_RightArrow.bmp");
	RightArrow_->SetPivot({ -200, -25 });
	UpArrow_ = CreateRenderer("Bag_UpArrow.bmp");
	UpArrow_->SetPivot({150, -280});
	UpArrow_->SetOrder(-1);
	DownArrow_ = CreateRenderer("Bag_DownArrow.bmp");
	DownArrow_->SetPivot({ 150, 90 });
	DownArrow_->SetOrder(-1);

	SelectArrow_ = CreateRenderer("Bag_CurrentArrow.bmp");
	SelectArrow_->SetPivot({-107, -260});

	ItemPreview_ = CreateRenderer("Bag_EnterArrow.bmp");
	ItemPreview_->SetPivot({-400, 225});

	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	BallList_.push_back(PokemonInfoManager::GetInst().FindItem("MonsterBall"));

	if (false == GameEngineInput::GetInst()->IsKey("LeftArrow"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftArrow", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("RightArrow", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("DownArrow", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("UpArrow", VK_UP);
	}

	ShowItemList();
}
void Bag::Update()
{
	MoveBag();
	MoveItem();

	ArrowMoveTime_ += GameEngineTime::GetDeltaTime();

	if (true == IsMove_)
	{
		BagMoveTime_ += GameEngineTime::GetDeltaTime();

		if (0.1f <= BagMoveTime_)
		{
			IsMove_ = false;
			BagMoveTime_ = 0.f;

			ChangeBag();
		}
	}

	if (0.3f <= ArrowMoveTime_
		&& false == IsArrowSync_)
	{
		IsArrowSync_ = true;
		ArrowMoveTime_ = 0.f;

		RightArrow_->SetPivot(RightArrow_->GetPivot() + float4{ 15, 0 });
		LeftArrow_->SetPivot(LeftArrow_->GetPivot() + float4{ -15, 0 });
		UpArrow_->SetPivot(UpArrow_->GetPivot() + float4{ 0, -15 });
		DownArrow_->SetPivot(DownArrow_->GetPivot() + float4{ 0, 15 });
	}

	if (0.3f <= ArrowMoveTime_
		&& true == IsArrowSync_)
	{
		IsArrowSync_ = false;
		ArrowMoveTime_ = 0.f;

		RightArrow_->SetPivot(RightArrow_->GetPivot() + float4{ -15, 0 });
		LeftArrow_->SetPivot(LeftArrow_->GetPivot() + float4{ 15, 0 });
		UpArrow_->SetPivot(UpArrow_->GetPivot() + float4{ 0, 15 });
		DownArrow_->SetPivot(DownArrow_->GetPivot() + float4{ 0, -15 });
	}

}

void Bag::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	HideFonts();
}

void Bag::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BagType_ = ItemType::ITEM;
	SelectIndex_ = 0;
	BagIndex_ = 0;

	ChangeBag();
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
		ShowItemList();
		break;
		
	case ItemType::KEYITEM:
		BagRedrerer_->SetImage("Bag_MiddleOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -48 });
		BagName_->SetImage("Bag_KeyItems.bmp");

		LeftArrow_->SetOrder(5);
		RightArrow_->SetOrder(5);
		ShowKeyItemList();
		break;

	case ItemType::BALL:
		BagRedrerer_->SetImage("Bag_RightOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -40 });
		BagName_->SetImage("Bag_PoketBalls.bmp");

		RightArrow_->SetOrder(-1);
		ShowBallList();
		break;
	}

	HideFonts();
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

				MoveSelectArrow();
				UpFonts();
				ShowItemInfo();
			}
			break;
		case ItemType::KEYITEM:
			if (KeyItemList_.size() > SelectIndex_)
			{
				++SelectIndex_;

				MoveSelectArrow();
				UpFonts();
				ShowKeyItemInfo();
			}
			break;
		case ItemType::BALL:
			if (BallList_.size() > SelectIndex_)
			{
				++SelectIndex_;

				MoveSelectArrow();
				UpFonts();
				ShowBallInfo();
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
				ShowItemInfo();
				DownFonts();
			}
			break;
		case ItemType::KEYITEM:
			if (0 < SelectIndex_)
			{
				--SelectIndex_;
				ShowKeyItemInfo();
				DownFonts();
			}
			break;
		case ItemType::BALL:
			if (0 < SelectIndex_)
			{
				--SelectIndex_;
				ShowBallInfo();
				DownFonts();
			}
			break;
		}

		MoveSelectArrow();
	}
}

void Bag::MoveSelectArrow()
{
	switch (SelectIndex_)
	{
	case 0:
		SelectArrow_->SetPivot({ -107, -260 });
		break;

	case 1:
		SelectArrow_->SetPivot({ -107, -195 });
		break;

	case 2:
		SelectArrow_->SetPivot({ -107, -130 });
		break;

	case 3:
		SelectArrow_->SetPivot({ -107, -65 });
		break;

	case 4:
		SelectArrow_->SetPivot({ -107, 0 });
		break;

	case 5:
		SelectArrow_->SetPivot({ -107, 60 });
		break;

	default:
		SelectArrow_->SetPivot({ -107, 60 });
		break;
	}
}

void Bag::ShowItemInfo()
{
	if (5 < SelectIndex_
		&& 5 < ItemList_.size())
	{
		UpArrow_->SetOrder(5);
	}

	else if (5 >= SelectIndex_
		&& 5 < ItemList_.size())
	{
		DownArrow_->SetOrder(5);
		UpArrow_->SetOrder(-1);
	}

	if (ItemList_.size() == SelectIndex_)
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");
		DownArrow_->SetOrder(-1);
		return;
	}

	//아이템 정보들
	ItemPreview_->SetImage(ItemList_[SelectIndex_]->GetNameCopy() + ".bmp");

	//GameEngineContentFont* BeginFont = GetLevel()->CreateActor<GameEngineContentFont>();
	//BeginFont->SetPosition({ 150, 460.f });
	//BeginFont->ShowString(ItemList_[SelectIndex_]->GetDesc(), true);
	//AllFonts_.push_back(BeginFont);
}

void Bag::ShowKeyItemInfo()
{
	if (5 < SelectIndex_
		&& 5 < KeyItemList_.size())
	{
		UpArrow_->SetOrder(5);
	}

	else if (5 >= SelectIndex_
		&& 5 < KeyItemList_.size())
	{
		DownArrow_->SetOrder(5);
		UpArrow_->SetOrder(-1);
	}

	if (KeyItemList_.size() == SelectIndex_)
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");
		DownArrow_->SetOrder(-1);
		return;
	}

	ItemPreview_->SetImage(KeyItemList_[SelectIndex_]->GetNameCopy() + ".bmp");
}

void Bag::ShowBallInfo()
{
	if (5 < SelectIndex_
		&& 5 < BallList_.size())
	{
		UpArrow_->SetOrder(5);
	}

	else if (5 >= SelectIndex_
		&& 5 < BallList_.size())
	{
		DownArrow_->SetOrder(5);
		UpArrow_->SetOrder(-1);
	}

	if (BallList_.size() == SelectIndex_)
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");
		DownArrow_->SetOrder(-1);
		return;
	}

	ItemPreview_->SetImage(BallList_[SelectIndex_]->GetNameCopy() + ".bmp");
}


void Bag::ShowItemList()
{
	DestroyFonts();

	UpArrow_->SetOrder(-1);
	DownArrow_->SetOrder(-1);

	if (0 == ItemList_.size())
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");

		GameEngineContentFont* EndFont = GetLevel()->CreateActor<GameEngineContentFont>();
		EndFont->SetPosition({ 380, 30.f });
		EndFont->ShowString("CLOSE", true);
		AllFonts_.push_back(EndFont);

		return;
	}

	else if (6 == ItemList_.size())
	{
		DownArrow_->SetOrder(5);
	}

	ItemPreview_->SetImage(ItemList_[0]->GetNameCopy() + ".bmp");

	ShowFonts(ItemList_);
}

void Bag::ShowKeyItemList()
{
	DestroyFonts();

	UpArrow_->SetOrder(-1);
	DownArrow_->SetOrder(-1);

	if (0 == KeyItemList_.size())
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");

		GameEngineContentFont* EndFont = GetLevel()->CreateActor<GameEngineContentFont>();
		EndFont->SetPosition({ 380, 30.f });
		EndFont->ShowString("CLOSE", true);
		AllFonts_.push_back(EndFont);

		return;
	}

	else if (6 == KeyItemList_.size())
	{
		DownArrow_->SetOrder(5);
	}

	ItemPreview_->SetImage(KeyItemList_[0]->GetNameCopy() + ".bmp");

	ShowFonts(KeyItemList_);
}

void Bag::ShowBallList()
{
	DestroyFonts();

	UpArrow_->SetOrder(-1);
	DownArrow_->SetOrder(-1);

	if (0 == BallList_.size())
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");

		GameEngineContentFont* EndFont = GetLevel()->CreateActor<GameEngineContentFont>();
		EndFont->SetPosition({ 380, 30.f });
		EndFont->ShowString("CLOSE", true);
		AllFonts_.push_back(EndFont);

		return;
	}

	else if (6 == BallList_.size())
	{
		DownArrow_->SetOrder(5);
	}

	ItemPreview_->SetImage(BallList_[0]->GetNameCopy() + ".bmp");

	ShowFonts(BallList_);
}

void Bag::UpFonts()
{
	if (7 > AllFonts_.size())
	{
		return;
	}

	if (5 < SelectIndex_
		&& AllFonts_.size() - 1 >= SelectIndex_)
	{
		for (int i = 0; i < AllFonts_.size(); ++i)
		{
			AllFonts_[i]->SetMove({ 0.f, -65.f });
		}
	}

	HideFonts();
}

void Bag::DownFonts()
{
	if (7 > AllFonts_.size())
	{
		return;
	}

 	if (5 >= SelectIndex_
		&& AllFonts_.size() - 1 <= SelectIndex_ + 1)
	{
		for (int i = 0; i < AllFonts_.size(); ++i)
		{
			AllFonts_[i]->SetMove({ 0.f, 65.f });
		}
	}

	HideFonts();
}

void Bag::HideFonts()
{
	for (int i = 0; i < AllFonts_.size(); ++i)
	{
		AllFonts_[i]->On();
	}

	for (int i = 0; i < AllFonts_.size(); ++i)
	{
		if (10 >= AllFonts_[i]->GetPosition().y)
		{
			AllFonts_[i]->Off();
		}

		else if (400 <= AllFonts_[i]->GetPosition().y)
		{
			AllFonts_[i]->Off();
		}
	}
}

void Bag::ShowFonts(std::vector<Item*>& _Fonts)
{
	GameEngineContentFont* BeginFont = GetLevel()->CreateActor<GameEngineContentFont>();
	BeginFont->SetPosition({ 380, 30.f });
	BeginFont->ShowString(_Fonts[0]->GetNameCopy(), true);
	AllFonts_.push_back(BeginFont);

	if (1 < _Fonts.size())
	{
		for (int i = 1; i < _Fonts.size(); ++i)
		{
			GameEngineContentFont* Fonts = GetLevel()->CreateActor<GameEngineContentFont>();
			Fonts->SetPosition(AllFonts_.back()->GetPosition() + float4{ 0, 65.f });
			Fonts->ShowString(_Fonts[i]->GetNameCopy(), true);
			AllFonts_.push_back(Fonts);
		}
	}

	GameEngineContentFont* EndFont = GetLevel()->CreateActor<GameEngineContentFont>();
	EndFont->SetPosition(AllFonts_.back()->GetPosition() + float4{ 0, 65.f });
	EndFont->ShowString("CLOSE", true);
	AllFonts_.push_back(EndFont);
}

void Bag::DestroyFonts()
{
	std::vector<GameEngineContentFont*>::iterator StartIter = AllFonts_.begin();
	std::vector<GameEngineContentFont*>::iterator EndIter = AllFonts_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			(*StartIter)->Death();
		}
	}

	AllFonts_.clear();
}
