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
	, ItemNameFonts_{nullptr}
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
	SelectArrow_->SetPivot({ -107, -250 });

	ItemPreview_ = CreateRenderer("Bag_EnterArrow.bmp");
	ItemPreview_->SetPivot({-400, 225});

	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	ItemList_.push_back(PokemonInfoManager::GetInst().FindItem("Potion"));
	BallList_.push_back(PokemonInfoManager::GetInst().FindItem("MonsterBall"));
	BallList_.push_back(PokemonInfoManager::GetInst().FindItem("MonsterBall"));
	BallList_.push_back(PokemonInfoManager::GetInst().FindItem("MonsterBall"));
	BallList_.push_back(PokemonInfoManager::GetInst().FindItem("MonsterBall"));
	
	BagDialog_ = CreateRenderer("DialogBox_Bag.bmp");
	BagDialog_->SetPivot({200, 200 });

	if (false == GameEngineInput::GetInst()->IsKey("LeftArrow"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftArrow", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("RightArrow", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("DownArrow", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("UpArrow", VK_UP);
	}

	ShowItemList();
	ShowItemInfo();
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
			BagRedrerer_->PlusPivot({ 0, -20 });

			SelectIndex_ = 0;
			SelectArrow_->SetPivot({ -107, -250 });

			--BagIndex_;
			BagType_ = static_cast<ItemType>(BagIndex_);
		}
	}

	else if (true == GameEngineInput::GetInst()->IsDown("RightArrow"))
	{
		if (2 > BagIndex_)
		{
			IsMove_ = true;
			BagRedrerer_->PlusPivot({ 0, -20 });

			SelectIndex_ = 0;
			SelectArrow_->SetPivot({ -107, -250 });

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
		ShowItemInfo();
		break;
		
	case ItemType::KEYITEM:
		BagRedrerer_->SetImage("Bag_MiddleOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -48 });
		BagName_->SetImage("Bag_KeyItems.bmp");

		LeftArrow_->SetOrder(5);
		RightArrow_->SetOrder(5);
		ShowKeyItemList();
		ShowKeyItemInfo();
		break;

	case ItemType::BALL:
		BagRedrerer_->SetImage("Bag_RightOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -40 });
		BagName_->SetImage("Bag_PoketBalls.bmp");

		RightArrow_->SetOrder(-1);
		ShowBallList();
		ShowBallInfo();
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
			if (ItemNameFonts_.size() - 1 > SelectIndex_)
			{
				++SelectIndex_;

				MoveSelectArrow();
				UpFonts();
				ShowItemInfo();
			}
			break;
		case ItemType::KEYITEM:
			if (ItemNameFonts_.size() - 1 > SelectIndex_)
			{
				++SelectIndex_;

				MoveSelectArrow();
				UpFonts();
				ShowKeyItemInfo();
			}
			break;
		case ItemType::BALL:
			if (ItemNameFonts_.size() - 1 > SelectIndex_)
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
		SelectArrow_->SetPivot({ -107, -250 });
		break;

	case 1:
		SelectArrow_->SetPivot({ -107, -185 });
		break;

	case 2:
		SelectArrow_->SetPivot({ -107, -120 });
		break;

	case 3:
		SelectArrow_->SetPivot({ -107, -55 });
		break;

	case 4:
		SelectArrow_->SetPivot({ -107, 10 });
		break;

	case 5:
		SelectArrow_->SetPivot({ -107, 70 });
		break;

	default:
		SelectArrow_->SetPivot({ -107, 70 });
		break;
	}
}

void Bag::ShowItemInfo()
{
	DestroyDescFonts();

	if (5 < SelectIndex_
		&& 5 < ItemList_.size()
		&& 5 < ItemNameFonts_.size())
	{
		UpArrow_->SetOrder(5);
	}

	else if (5 >= SelectIndex_
		&& 5 < ItemList_.size()
		&& 5 < ItemNameFonts_.size())
	{
		DownArrow_->SetOrder(5);
		UpArrow_->SetOrder(-1);
	}

	if (ItemNameFonts_.size() - 1 == SelectIndex_
		|| ItemList_.size() == SelectIndex_
		|| 0 == ItemList_.size())
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");

		GameEngineContentFont* DescFont = GetLevel()->CreateActor<GameEngineContentFont>();
		DescFont->SetPosition({ 150, 460.f });
		DescFont->ShowString("CLOSE BAG", true);
		ItemDescFonts_.push_back(DescFont);

		DownArrow_->SetOrder(-1);
		return;
	}

	//아이템 정보
	ItemPreview_->SetImage(ItemList_[SelectIndex_]->GetNameCopy() + ".bmp");

	GameEngineContentFont* DescFont = GetLevel()->CreateActor<GameEngineContentFont>();
	DescFont->SetPosition({ 150, 460.f });
	DescFont->ShowString(ItemList_[SelectIndex_]->GetDesc(), true);
	ItemDescFonts_.push_back(DescFont);
}

void Bag::ShowKeyItemInfo()
{
	DestroyDescFonts();

	if (5 < SelectIndex_
		&& 5 < ItemList_.size()
		&& 5 < ItemNameFonts_.size())
	{
		UpArrow_->SetOrder(5);
	}

	else if (5 >= SelectIndex_
		&& 5 < ItemList_.size()
		&& 5 < ItemNameFonts_.size())
	{
		DownArrow_->SetOrder(5);
		UpArrow_->SetOrder(-1);
	}


	if (ItemNameFonts_.size() - 1 == SelectIndex_
		|| KeyItemList_.size() == SelectIndex_
		|| 0 == KeyItemList_.size())
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");

		GameEngineContentFont* DescFont = GetLevel()->CreateActor<GameEngineContentFont>();
		DescFont->SetPosition({ 150, 460.f });
		DescFont->ShowString("CLOSE BAG", true);
		ItemDescFonts_.push_back(DescFont);

		DownArrow_->SetOrder(-1);
		return;
	}

	ItemPreview_->SetImage(KeyItemList_[SelectIndex_]->GetNameCopy() + ".bmp");

	GameEngineContentFont* DescFont = GetLevel()->CreateActor<GameEngineContentFont>();
	DescFont->SetPosition({ 150, 460.f });
	DescFont->ShowString(KeyItemList_[SelectIndex_]->GetDesc(), true);
	ItemDescFonts_.push_back(DescFont);
}

void Bag::ShowBallInfo()
{
	DestroyDescFonts();

	if (5 < SelectIndex_
		&& 5 < ItemList_.size()
		&& 5 < ItemNameFonts_.size())
	{
		UpArrow_->SetOrder(5);
	}

	else if (5 >= SelectIndex_
		&& 5 < ItemList_.size()
		&& 5 < ItemNameFonts_.size())
	{
		DownArrow_->SetOrder(5);
		UpArrow_->SetOrder(-1);
	}


	if (ItemNameFonts_.size() - 1 == SelectIndex_
		|| BallList_.size() == SelectIndex_
		|| 0 == BallList_.size())

	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");

		GameEngineContentFont* DescFont = GetLevel()->CreateActor<GameEngineContentFont>();
		DescFont->SetPosition({ 150, 460.f });
		DescFont->ShowString("CLOSE BAG", true);
		ItemDescFonts_.push_back(DescFont);

		DownArrow_->SetOrder(-1);
		return;
	}

	ItemPreview_->SetImage(BallList_[SelectIndex_]->GetNameCopy() + ".bmp");

	GameEngineContentFont* DescFont = GetLevel()->CreateActor<GameEngineContentFont>();
	DescFont->SetPosition({ 150, 460.f });
	DescFont->ShowString(BallList_[SelectIndex_]->GetDesc(), true);
	ItemDescFonts_.push_back(DescFont);
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
		EndFont->SetPosition({ 380, 40.f });
		EndFont->ShowString("CLOSE", true);
		ItemNameFonts_.push_back(EndFont);

		return;
	}

	else if (6 == ItemNameFonts_.size())
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
		EndFont->SetPosition({ 380, 40.f });
		EndFont->ShowString("CLOSE", true);
		ItemNameFonts_.push_back(EndFont);

		return;
	}

	else if (6 == ItemNameFonts_.size())
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
		EndFont->SetPosition({ 380, 40.f });
		EndFont->ShowString("CLOSE", true);
		ItemNameFonts_.push_back(EndFont);

		return;
	}

	else if (6 == ItemNameFonts_.size())
	{
		DownArrow_->SetOrder(5);
	}

	ItemPreview_->SetImage(BallList_[0]->GetNameCopy() + ".bmp");

	ShowFonts(BallList_);
}

void Bag::UpFonts()
{
	if (7 > ItemNameFonts_.size())
	{
		return;
	}

	if (5 < SelectIndex_
		&& ItemNameFonts_.size() - 1 >= SelectIndex_)
	{
		for (int i = 0; i < ItemNameFonts_.size(); ++i)
		{
			ItemNameFonts_[i]->SetMove({ 0.f, -65.f });
		}
	}

	HideFonts();
}

void Bag::DownFonts()
{
	if (7 > ItemNameFonts_.size())
	{
		return;
	}

 	if (5 >= SelectIndex_
		&& ItemNameFonts_.size() - 1 <= SelectIndex_ + 1)
	{
		for (int i = 0; i < ItemNameFonts_.size(); ++i)
		{
			ItemNameFonts_[i]->SetMove({ 0.f, 65.f });
		}
	}

	HideFonts();
}

void Bag::HideFonts()
{
	for (int i = 0; i < ItemNameFonts_.size(); ++i)
	{
		ItemNameFonts_[i]->On();
	}

	for (int i = 0; i < ItemNameFonts_.size(); ++i)
	{
		if (10 >= ItemNameFonts_[i]->GetPosition().y)
		{
			ItemNameFonts_[i]->Off();
		}

		else if (400 <= ItemNameFonts_[i]->GetPosition().y)
		{
			ItemNameFonts_[i]->Off();
		}
	}
}

void Bag::ShowFonts(std::vector<Item*>& _List)
{
	GameEngineContentFont* BeginFont = GetLevel()->CreateActor<GameEngineContentFont>();
	BeginFont->SetPosition({ 380, 40.f });
	BeginFont->ShowString(_List[0]->GetNameCopy(), true);
	ItemNameFonts_.push_back(BeginFont);

	if (1 < _List.size())
	{
		for (int i = 1; i < _List.size(); ++i)
		{
			if (_List[i - 1]->GetNameConstRef() == _List[i]->GetNameConstRef())
			{
				DestroyOverlapFonts();

				GameEngineContentFont* OverlapFont = GetLevel()->CreateActor<GameEngineContentFont>();
				OverlapFont->SetPosition({ 800, 40.f });
				OverlapFont->ShowString("x " + std::to_string(i + 1), true);
				ItemOverlapFonts_.push_back(OverlapFont);

				continue;
			}

			GameEngineContentFont* Fonts = GetLevel()->CreateActor<GameEngineContentFont>();
			Fonts->SetPosition(ItemNameFonts_.back()->GetPosition() + float4{ 0, 65.f });
			Fonts->ShowString(_List[i]->GetNameCopy(), true);
			ItemNameFonts_.push_back(Fonts);
		}
	}

	GameEngineContentFont* EndFont = GetLevel()->CreateActor<GameEngineContentFont>();
	EndFont->SetPosition(ItemNameFonts_.back()->GetPosition() + float4{ 0, 65.f });
	EndFont->ShowString("CLOSE", true);
	ItemNameFonts_.push_back(EndFont);
}

void Bag::DestroyFonts()
{
	DestroyNameFonts();
	DestroyDescFonts();
	DestroyOverlapFonts();
}

void Bag::DestroyNameFonts()
{
	std::vector<GameEngineContentFont*>::iterator StartIter = ItemNameFonts_.begin();
	std::vector<GameEngineContentFont*>::iterator EndIter = ItemNameFonts_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			(*StartIter)->Death();
		}
	}

	ItemNameFonts_.clear();

}

void Bag::DestroyDescFonts()
{
	std::vector<GameEngineContentFont*>::iterator StartIter = ItemDescFonts_.begin();
	std::vector<GameEngineContentFont*>::iterator EndIter = ItemDescFonts_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			(*StartIter)->Death();
		}
	}

	ItemDescFonts_.clear();
}

void Bag::DestroyOverlapFonts()
{
	std::vector<GameEngineContentFont*>::iterator StartIter = ItemOverlapFonts_.begin();
	std::vector<GameEngineContentFont*>::iterator EndIter = ItemOverlapFonts_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			(*StartIter)->Death();
		}
	}

	ItemOverlapFonts_.clear();
}

