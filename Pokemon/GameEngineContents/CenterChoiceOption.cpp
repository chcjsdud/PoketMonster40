#include "CenterChoiceOption.h"
#include <GameEngineBase/GameEngineInput.h>
#include "InteractionText.h"

CenterChoiceOption::CenterChoiceOption() 
	: UIRenderer_(nullptr)
	, ArrowRenderer_(nullptr)
	, ParentText_(nullptr)
	, CurrentIndex_(0)
{
}

CenterChoiceOption::~CenterChoiceOption() 
{
}

void CenterChoiceOption::SetParent(InteractionText* _Parent)
{
	ParentText_ = _Parent;
}

void CenterChoiceOption::Start()
{
	UIRenderer_ = CreateRenderer("DialogBox_Bag.bmp");
	UIRenderer_->SetPivot({ 250, 150 });

	ArrowRenderer_ = CreateRenderer("Bag_CurrentArrow.bmp");
	ArrowRenderer_->SetPivot({ 200, 150 });

	ArrowPos_.push_back({ 200, 100 });
	ArrowPos_.push_back({ 200, 200 });
}

void CenterChoiceOption::Update()
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
	if (1 < CurrentIndex_)
	{
		CurrentIndex_ = 1;
	}

	ArrowRenderer_->SetPivot(ArrowPos_[CurrentIndex_]);
}

void CenterChoiceOption::SelectIndex()
{
	switch (CurrentIndex_)
	{
	case 0:
	{
		//InteractionText* TmpText = GetLevel()->CreateActor<InteractionText>();
		//TmpText->SetPosition(GetPosition());
		ParentText_->ClearText();
		ParentText_->AddText("Okay, I'll take your POKEMON for a");
		ParentText_->AddText("few seconds.");
		ParentText_->AddText("Thank you for waiting.");
		ParentText_->AddText("We've restored your POKEMON to");
		ParentText_->AddText("full health.");
		ParentText_->AddText("We hope to see you again!");
		ParentText_->Setting();
	}
		break;
	case 1:
	{
		ParentText_->ClearText();
		ParentText_->AddText("We hope to see you again!");
		ParentText_->Setting();
	}
		break;
	default:
		break;
	}

	ParentText_->ChoiceEnd();
	Death();
}
