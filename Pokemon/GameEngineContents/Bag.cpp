#include "Bag.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "PokemonInfoManager.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include "Item.h"
#include "Pokemon.h"
#include "PokemonInfoManager.h"

Bag::Bag()
	: BagType_(ItemType::ITEM)
	, BagRedrerer_(nullptr)
	, BagName_(nullptr)
	, BagDialog_(nullptr)
	, DialogBox_(nullptr)
	, DialogArrow_(nullptr)
	, LeftArrow_(nullptr)
	, RightArrow_(nullptr)
	, UpArrow_(nullptr)
	, DownArrow_(nullptr)
	, SelectArrow_(nullptr)
	, SelectIndex_(0)
	, ItemPreview_(nullptr)
	, ItemNameFonts_{}
	, BagIndex_(0)
	, BagMoveTime_(0.f)
	, IsMove_(false)
	, ArrowMoveTime_(0.f)
	, IsArrowSync_(false)
	, IsDialogOn_(false)
	, DialogIndex_(0)
	, CurrentItem_(nullptr)
	, CurrentPokemon_(nullptr)
{

}

Bag::~Bag()
{
	DestroyBag();
}

void Bag::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("LeftArrow"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftArrow", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("RightArrow", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("DownArrow", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("UpArrow", VK_UP);
		GameEngineInput::GetInst()->CreateKey("DialogOn", VK_LCONTROL);
		GameEngineInput::GetInst()->CreateKey("Select", VK_TAB);
	}
}

void Bag::Update()
{
	if (false == IsDialogOn_)
	{
		MoveBag();
		MoveItem();
	}

	ActiveDialog();
	MoveDialog();

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
		ShowItemInfo(ItemList_);
		break;

	case ItemType::KEYITEM:
		BagRedrerer_->SetImage("Bag_MiddleOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -48 });
		BagName_->SetImage("Bag_KeyItems.bmp");

		LeftArrow_->SetOrder(5);
		RightArrow_->SetOrder(5);
		ShowKeyItemList();
		ShowItemInfo(KeyItemList_);
		break;

	case ItemType::BALL:
		BagRedrerer_->SetImage("Bag_RightOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -40 });
		BagName_->SetImage("Bag_PoketBalls.bmp");

		RightArrow_->SetOrder(-1);
		ShowBallList();
		ShowItemInfo(BallList_);
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
				ShowItemInfo(ItemList_);
			}
			break;
		case ItemType::KEYITEM:
			if (ItemNameFonts_.size() - 1 > SelectIndex_)
			{
				++SelectIndex_;

				MoveSelectArrow();
				UpFonts();
				ShowItemInfo(KeyItemList_);
			}
			break;
		case ItemType::BALL:
			if (ItemNameFonts_.size() - 1 > SelectIndex_)
			{
				++SelectIndex_;

				MoveSelectArrow();
				UpFonts();
				ShowItemInfo(BallList_);
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
				ShowItemInfo(ItemList_);
				DownFonts();
			}
			break;
		case ItemType::KEYITEM:
			if (0 < SelectIndex_)
			{
				--SelectIndex_;
				ShowItemInfo(KeyItemList_);
				DownFonts();
			}
			break;
		case ItemType::BALL:
			if (0 < SelectIndex_)
			{
				--SelectIndex_;
				ShowItemInfo(BallList_);
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

void Bag::ShowItemInfo(std::vector<class Item*>& _List)
{
	DestroyDescFonts();

	if (5 < SelectIndex_
		&& 5 < _List.size()
		&& 5 < ItemNameFonts_.size())
	{
		UpArrow_->SetOrder(5);
	}

	else if (5 >= SelectIndex_
		&& 5 < _List.size()
		&& 5 < ItemNameFonts_.size())
	{
		DownArrow_->SetOrder(5);
		UpArrow_->SetOrder(-1);
	}

	if (ItemNameFonts_.size() - 1 == SelectIndex_
		|| _List.size() == SelectIndex_
		|| 0 == _List.size())
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");

		GameEngineContentFont* DescFont = GetLevel()->CreateActor<GameEngineContentFont>(55);
		DescFont->SetPosition(GetPosition() + float4{-320, 150});
		DescFont->ShowString("CLOSE BAG", true);
		ItemDescFonts_.push_back(DescFont);

		DownArrow_->SetOrder(-1);
		return;
	}

	//아이템 정보
	ItemPreview_->SetImage(_List[SelectIndex_]->GetInfo()->GetNameCopy() + ".bmp");

	GameEngineContentFont* DescFont = GetLevel()->CreateActor<GameEngineContentFont>(55);
	DescFont->SetPosition(GetPosition() + float4{ -320, 150 });
	DescFont->ShowString(_List[SelectIndex_]->GetInfo()->GetDesc(), true);
	ItemDescFonts_.push_back(DescFont);
}

void Bag::ActiveDialog()
{
	if (true == GameEngineInput::GetInst()->IsDown("DialogOn")
		&& false == IsDialogOn_)
	{
		OnDialog();
	}

	else if (true == GameEngineInput::GetInst()->IsDown("DialogOn")
		&& true == IsDialogOn_)
	{
		CloseDialog();
	}
}

void Bag::OnDialog()
{
	if (ItemNameFonts_.size() - 1 == SelectIndex_)
	{
		return;
	}

	DestroyDialogFonts();
	DestroyDescFonts();

	IsDialogOn_ = true;
	BagDialog_->On();
	DialogBox_->On();
	DialogArrow_->On();

	DialogIndex_ = 0;

	DialogArrow_->SetPivot({ 240, 130 });

	if ("BattleLevel" == GetLevel()->GetNameConstRef())
	{
		DialogArrow_->SetPivot({ 240, 190 });
	}

	GameEngineContentFont* SelcetFont = GetLevel()->CreateActor<GameEngineContentFont>(55);
	SelcetFont->SetPosition(GetPosition() + float4{-300, 160});
	
	switch (BagType_)
	{
	case ItemType::ITEM:
		if (ItemList_.size() == 0)
		{
			return;
		}
		SelcetFont->ShowString(ItemList_[SelectIndex_]->GetInfo()->GetNameConstRef() + " is \\Selected.", true);
		break;
	case ItemType::KEYITEM:
		if (KeyItemList_.size() == 0)
		{
			return;
		}
		SelcetFont->ShowString(KeyItemList_[SelectIndex_]->GetInfo()->GetNameConstRef() + " is \\Selected.", true);
		break;
	case ItemType::BALL:
		if (BallList_.size() == 0)
		{
			return;
		}
		SelcetFont->ShowString(BallList_[SelectIndex_]->GetInfo()->GetNameConstRef() + " is \\Selected.", true);
		break;
	}

	DialogFonts_.push_back(SelcetFont);

	if ("BattleLevel" != GetLevel()->GetNameConstRef())
	{
		GameEngineContentFont* Give = GetLevel()->CreateActor<GameEngineContentFont>(55);
		Give->SetPosition(GetPosition() + float4{250, 100});
		Give->ShowString("GIVE", true);
		DialogFonts_.push_back(Give);

		GameEngineContentFont* Toss = GetLevel()->CreateActor<GameEngineContentFont>(55);
		Toss->SetPosition(GetPosition() + float4{ 250, 160 });
		Toss->ShowString("TOSS", true);
		DialogFonts_.push_back(Toss);

		GameEngineContentFont* Cancle = GetLevel()->CreateActor<GameEngineContentFont>(55);
		Cancle->SetPosition(GetPosition() + float4{ 250, 220 });
		Cancle->ShowString("CANCLE", true);
		DialogFonts_.push_back(Cancle);
	}

	else if ("BattleLevel" == GetLevel()->GetNameConstRef())
	{
		BagDialog_->SetImage("DialogBox_Bag_Battle.bmp");
		BagDialog_->SetPivot({ 335, 215 });

		GameEngineContentFont* Use = GetLevel()->CreateActor<GameEngineContentFont>(55);
		Use->SetPosition(GetPosition() + float4{ 250, 130 });
		Use->ShowString("USE", true);
		DialogFonts_.push_back(Use);

		GameEngineContentFont* Cancle = GetLevel()->CreateActor<GameEngineContentFont>(55);
		Cancle->SetPosition(GetPosition() + float4{ 250, 190 });
		Cancle->ShowString("CANCLE", true);
		DialogFonts_.push_back(Cancle);
	}

	UpArrow_->Off();
	DownArrow_->Off();
	RightArrow_->Off();
	LeftArrow_->Off();	
}

void Bag::MoveDialog()
{
	if (true == IsDialogOn_)
	{
		if (true == GameEngineInput::GetInst()->IsDown("DownArrow"))
		{
			if ("BattleLevel" == GetLevel()->GetNameConstRef()
				&& DialogIndex_ >= 1)
			{
				return;
			}

			++DialogIndex_;

			switch (DialogIndex_)
			{
			case 0:
				if ("BattleLevel" == GetLevel()->GetNameConstRef())
				{
					DialogArrow_->SetPivot({ 240, 190 });
					break;
				}
				DialogArrow_->SetPivot({ 240, 130 });
				break;
			case 1:
				if ("BattleLevel" == GetLevel()->GetNameConstRef())
				{
					DialogArrow_->SetPivot({ 240, 250 });
					break;
				}
				DialogArrow_->SetPivot({ 240, 190 });
				break;
			case 2:
				DialogArrow_->SetPivot({ 240, 250 });
				break;
			}
		}


		else if (true == GameEngineInput::GetInst()->IsDown("UpArrow"))
		{
			if (0 == DialogIndex_)
			{
				return;
			}

			--DialogIndex_;

			switch (DialogIndex_)
			{
			case 0:
				if ("BattleLevel" == GetLevel()->GetNameConstRef())
				{
					DialogArrow_->SetPivot({ 240, 190 });
					break;
				}
				DialogArrow_->SetPivot({ 240, 130 });
				break;
			case 1:
				if ("BattleLevel" == GetLevel()->GetNameConstRef())
				{
					DialogArrow_->SetPivot({ 240, 250 });
					break;
				}
				DialogArrow_->SetPivot({ 240, 190 });
				break;
			case 2:
				DialogArrow_->SetPivot({ 240, 250 });
				break;
			}
		}

		else if (true == GameEngineInput::GetInst()->IsDown("Select"))
		{
			SelectDialog();
		}
	}
}

void Bag::SelectDialog()
{
	switch (DialogIndex_)
	{
	case 0:
		if ("BattleLevel" == GetLevel()->GetNameConstRef())
		{
			//Use
			break;
		}
		//Give
		if (ItemType::KEYITEM == BagType_)
		{
			return;
		}

		if (ItemType::ITEM == BagType_)
		{
			if (0 == ItemList_.size())
			{
				ShowFonts(ItemList_);
				break;
			}

			CurrentPokemon_->GetInfo()->SetMyItem(ItemList_[SelectIndex_]);
			Item* NewItem = ItemList_.back();
			delete NewItem;
			NewItem = nullptr;
			ItemList_.pop_back();
			ShowFonts(ItemList_);
			//포켓몬 스탯창 가기
		}
		if (ItemType::BALL == BagType_)
		{
			if (0 == BallList_.size())
			{
				ShowFonts(BallList_);
				break;
			}

			CurrentPokemon_->GetInfo()->SetMyItem(BallList_[SelectIndex_]);
			Item* NewItem = BallList_.back();
			delete NewItem;
			NewItem = nullptr;
			BallList_.pop_back();
			ShowFonts(BallList_);
			//포켓몬 스탯창 가기
		}
		break;
	case 1:
		if ("BattleLevel" == GetLevel()->GetNameConstRef())
		{
			CloseDialog();
		}
		//Toss
		if (ItemType::KEYITEM == BagType_)
		{
			return;
		}
		if (ItemType::ITEM == BagType_)
		{
			ItemList_.pop_back();
			ShowFonts(ItemList_);

		}
		if (ItemType::BALL == BagType_)
		{
			BallList_.pop_back();
			ShowFonts(BallList_);
		}
		break;
	case 2:
		CloseDialog();
	}
}

void Bag::CloseDialog()
{
	IsDialogOn_ = false;
	BagDialog_->Off();
	DialogBox_->Off();
	DialogArrow_->Off();

	LeftArrow_->On();
	RightArrow_->On();

	DestroyDialogFonts();

	switch (BagType_)
	{
	case ItemType::ITEM:
		LeftArrow_->SetOrder(-1);
		ShowItemList();
		ShowItemInfo(ItemList_);
		break;

	case ItemType::KEYITEM:
		LeftArrow_->SetOrder(5);
		RightArrow_->SetOrder(5);
		ShowKeyItemList();
		ShowItemInfo(KeyItemList_);
		break;

	case ItemType::BALL:
		RightArrow_->SetOrder(-1);
		ShowBallList();
		ShowItemInfo(BallList_);
		break;
	}
}


void Bag::ShowItemList()
{
	DestroyFonts();

	UpArrow_->SetOrder(-1);
	DownArrow_->SetOrder(-1);

	if (0 == ItemList_.size())
	{
		ItemPreview_->SetImage("Bag_EnterArrow.bmp");

		GameEngineContentFont* EndFont = GetLevel()->CreateActor<GameEngineContentFont>(55);
		EndFont->SetPosition(GetPosition() + float4{ -90, -285 });
		EndFont->ShowString("CLOSE", true);
		ItemNameFonts_.push_back(EndFont);

		return;
	}

	else if (6 == ItemNameFonts_.size())
	{
		DownArrow_->SetOrder(5);
	}

	ItemPreview_->SetImage(ItemList_[0]->GetInfo()->GetNameCopy() + ".bmp");

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

		GameEngineContentFont* EndFont = GetLevel()->CreateActor<GameEngineContentFont>(55);
		EndFont->SetPosition(GetPosition() + float4{ -90, -285 });
		EndFont->ShowString("CLOSE", true);
		ItemNameFonts_.push_back(EndFont);

		return;
	}

	else if (6 == ItemNameFonts_.size())
	{
		DownArrow_->SetOrder(5);
	}

	ItemPreview_->SetImage(KeyItemList_[0]->GetInfo()->GetNameCopy() + ".bmp");

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

		GameEngineContentFont* EndFont = GetLevel()->CreateActor<GameEngineContentFont>(55);
		EndFont->SetPosition(GetPosition() + float4{ -90, -285 });
		EndFont->ShowString("CLOSE", true);
		ItemNameFonts_.push_back(EndFont);

		return;
	}

	else if (6 == ItemNameFonts_.size())
	{
		DownArrow_->SetOrder(5);
	}

	ItemPreview_->SetImage(BallList_[0]->GetInfo()->GetNameCopy() + ".bmp");

	ShowFonts(BallList_);
}

void Bag::BagInit()
{
	BagType_ = ItemType::ITEM;
	SelectIndex_ = 0;
	BagIndex_ = 0;

	IsDialogOn_ = false;
	DialogIndex_ = 0;

	CreateRenderer("Bag_Back.bmp");

	BagRedrerer_ = CreateRenderer("Bag_LeftOpen.bmp");
	BagRedrerer_->SetPivot({ -317, -40 });

	BagName_ = CreateRenderer("Bag_Items.bmp");
	BagName_->SetPivot({ -314, -258 });

	LeftArrow_ = CreateRenderer("Bag_LeftArrow.bmp");
	LeftArrow_->SetPivot({ -436, -25 });
	LeftArrow_->SetOrder(-1);
	RightArrow_ = CreateRenderer("Bag_RightArrow.bmp");
	RightArrow_->SetPivot({ -200, -25 });
	UpArrow_ = CreateRenderer("Bag_UpArrow.bmp");
	UpArrow_->SetPivot({ 150, -280 });
	UpArrow_->SetOrder(-1);
	DownArrow_ = CreateRenderer("Bag_DownArrow.bmp");
	DownArrow_->SetPivot({ 150, 90 });
	DownArrow_->SetOrder(-1);

	SelectArrow_ = CreateRenderer("Bag_CurrentArrow.bmp");
	SelectArrow_->SetPivot({ -107, -250 });

	ItemPreview_ = CreateRenderer("Bag_EnterArrow.bmp");
	ItemPreview_->SetPivot({ -400, 225 });

	ItemList_.push_back(PokemonInfoManager::GetInst().CreateItem("Potion"));
	ItemList_.push_back(PokemonInfoManager::GetInst().CreateItem("Potion"));
	BallList_.push_back(PokemonInfoManager::GetInst().CreateItem("PokeBall"));
	BallList_.push_back(PokemonInfoManager::GetInst().CreateItem("PokeBall"));

	BagDialog_ = CreateRenderer("DialogBox_Bag.bmp");
	BagDialog_->SetPivot({ 335, 190 });
	BagDialog_->Off();

	DialogBox_ = CreateRenderer("DialogBox_LogBox.bmp");
	DialogBox_->SetPivot({ -80, 224 });
	DialogBox_->Off();

	DialogArrow_ = CreateRenderer("Bag_CurrentArrow.bmp");
	DialogArrow_->SetPivot({ 240, 130 });
	DialogArrow_->Off();

	HideFonts();

	ShowItemList();
	ShowItemInfo(ItemList_);

	ChangeBag();

	CurrentPokemon_ = PokemonInfoManager::GetInst().CreatePokemon("Charmander");

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
	/*for (int i = 0; i < ItemNameFonts_.size(); ++i)
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
	}*/
}

void Bag::ShowFonts(std::vector<Item*>& _List)
{
	DestroyNameFonts();
	DestroyOverlapFonts();

	if (0 == _List.size())
	{
		GameEngineContentFont* EndFont = GetLevel()->CreateActor<GameEngineContentFont>(55);
		EndFont->SetPosition(GetPosition() + float4{-90, -285 });
		EndFont->ShowString("CLOSE", true);
		ItemNameFonts_.push_back(EndFont);

		return;
	}

	GameEngineContentFont* BeginFont = GetLevel()->CreateActor<GameEngineContentFont>(55);
	BeginFont->SetPosition(GetPosition() + float4{ -90, -285 });
	BeginFont->ShowString(_List[0]->GetInfo()->GetNameCopy(), true);
	ItemNameFonts_.push_back(BeginFont);

	if (1 < _List.size())
	{
		for (int i = 1; i < _List.size(); ++i)
		{
			if (_List[i - 1]->GetInfo()->GetNameConstRef() == _List[i]->GetInfo()->GetNameConstRef())
			{
				DestroyOverlapFonts();

				GameEngineContentFont* OverlapFont = GetLevel()->CreateActor<GameEngineContentFont>(55);
				OverlapFont->SetPosition(GetPosition() + float4{320, -280});
				OverlapFont->ShowString("x " + std::to_string(i + 1), true);
				ItemOverlapFonts_.push_back(OverlapFont);

				continue;
			}

			GameEngineContentFont* Fonts = GetLevel()->CreateActor<GameEngineContentFont>(55);
			Fonts->SetPosition(ItemNameFonts_.back()->GetPosition() + float4{ 0, 65.f });
			Fonts->ShowString(_List[i]->GetInfo()->GetNameCopy(), true);
			ItemNameFonts_.push_back(Fonts);
		}
	}

	GameEngineContentFont* EndFont = GetLevel()->CreateActor<GameEngineContentFont>(55);
	EndFont->SetPosition(ItemNameFonts_.back()->GetPosition() + float4{ 0, 65.f });
	EndFont->ShowString("CLOSE", true);
	ItemNameFonts_.push_back(EndFont);
}

void Bag::DestroyFonts()
{
	DestroyNameFonts();
	DestroyDescFonts();
	DestroyOverlapFonts();
	DestroyDialogFonts();
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

void Bag::DestroyDialogFonts()
{
	std::vector<GameEngineContentFont*>::iterator StartIter = DialogFonts_.begin();
	std::vector<GameEngineContentFont*>::iterator EndIter = DialogFonts_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			(*StartIter)->Death();
		}
	}

	DialogFonts_.clear();
}

void Bag::DestroyBag()
{
	BagRedrerer_->Death();
	BagName_->Death();
	BagDialog_->Death();
	DialogBox_->Death();
	DialogArrow_->Death();

	LeftArrow_->Death();
	RightArrow_->Death();
	UpArrow_->Death();
	DownArrow_->Death();

	SelectArrow_->Death(); //아이템 선택 화살표

	{
		std::vector<Item*>::iterator StartIter = ItemList_.begin();
		std::vector<Item*>::iterator EndIter = ItemList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if ((*StartIter) != nullptr)
			{
				delete (*StartIter);
				(*StartIter) = nullptr;
			}
		}
	}

	ItemList_.clear();

	{
		std::vector<Item*>::iterator StartIter = KeyItemList_.begin();
		std::vector<Item*>::iterator EndIter = KeyItemList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if ((*StartIter) != nullptr)
			{
				delete (*StartIter);
				(*StartIter) = nullptr;
			}
		}
	}

	KeyItemList_.clear();

	{
		std::vector<Item*>::iterator StartIter = BallList_.begin();
		std::vector<Item*>::iterator EndIter = BallList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if ((*StartIter) != nullptr)
			{
				delete (*StartIter);
				(*StartIter) = nullptr;
			}
		}
	}

	BallList_.clear();

	ItemPreview_->Death(); //현재 선택한 아이템 이미지

	DestroyFonts();

	CurrentItem_ = nullptr;

	delete CurrentPokemon_; //받아올 때는 지우자
	CurrentPokemon_ = nullptr;
}

