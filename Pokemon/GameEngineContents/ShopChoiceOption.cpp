#include "ShopChoiceOption.h"
#include <GameEngineBase/GameEngineInput.h>
#include "InteractionText.h"

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
	UIRenderer_ = CreateRenderer("DialogBox_Bag.bmp");
	UIRenderer_->SetPivot({ -250, -150 });

	ArrowRenderer_ = CreateRenderer("Bag_CurrentArrow.bmp");
	ArrowRenderer_->SetPivot({ -200, -150 });

	ArrowPos_.push_back({-200, -250});
	ArrowPos_.push_back({-200, -150});
	ArrowPos_.push_back({-200, -50});
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
	switch (CurrentIndex_)
	{
	case 0:
	{
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
	}
	break;
	default:
		break;
	}

	ParentText_->ChoiceEnd();
	Death();
}
