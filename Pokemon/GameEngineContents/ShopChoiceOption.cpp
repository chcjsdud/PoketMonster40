#include "ShopChoiceOption.h"
#include <GameEngineBase/GameEngineInput.h>
#include "InteractionText.h"
#include "Shop.h"
#include "PlayerRed.h"
#include <GameEngineBase/GameEngineWindow.h>

ShopChoiceOption::ShopChoiceOption() 
	: UIRenderer_(nullptr)
	, ArrowRenderer_(nullptr)
	, ParentText_(nullptr)
	, CurrentIndex_(0)
{
}

ShopChoiceOption::~ShopChoiceOption() 
{
}

void ShopChoiceOption::SetParent(InteractionText* _Parent)
{
	ParentText_ = _Parent;
}

void ShopChoiceOption::Start()
{
	UIRenderer_ = CreateRenderer("ChoiceOption2.bmp");
	UIRenderer_->SetPivot({ -225, -190 });

	ArrowRenderer_ = CreateRenderer("ChoiceOption_Arrow.bmp");
	ArrowRenderer_->SetPivot({ -165, -190 });

	ArrowPos_.push_back({-400, -250});
	ArrowPos_.push_back({-400, -190 });
	ArrowPos_.push_back({-400, -120});
}

void ShopChoiceOption::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Z"))
	{
		SelectIndex();
	}
	if (true == GameEngineInput::GetInst()->IsDown("Up"))
	{
		CurrentIndex_ -= 1;
	}
	if (true == GameEngineInput::GetInst()->IsDown("Down"))
	{
		CurrentIndex_ += 1;
	}

	if (CurrentIndex_ < 0)
	{
		CurrentIndex_ = 0;
	}
	if (2 < CurrentIndex_)
	{
		CurrentIndex_ = 2;
	}

	ArrowRenderer_->SetPivot(ArrowPos_[CurrentIndex_]);
}

void ShopChoiceOption::SelectIndex()
{
	if (nullptr != dynamic_cast<Shop*>(PlayerRed::MainRed_->GetChildUI()))
	{
		return;
	}

	switch (CurrentIndex_)
	{
	case 0:
	{
		ParentText_->ClearText();
		ParentText_->AddText("Is there anything else I can do?");
		ParentText_->Setting();

		PlayerRed::MainRed_->SetChildUI(GetLevel()->CreateActor<Shop>(60, "Shop"));
		PlayerRed::MainRed_->GetChildUI()->SetPosition(PlayerRed::MainRed_->GetPosition() - GameEngineWindow::GetScale().Half());
		dynamic_cast<Shop*>(PlayerRed::MainRed_->GetChildUI())->SetPlayerItemList(PlayerRed::MainRed_->GetItemList());
		dynamic_cast<Shop*>(PlayerRed::MainRed_->GetChildUI())->ShopInit();
	}
	break;
	case 1:
	{
	}
	break;
	case 2:
	{
		ParentText_->ClearText();
		ParentText_->AddText("Please come again!");
		ParentText_->Setting();
		ParentText_->ChoiceEnd();
		Death();
	}
	break;
	}
}
