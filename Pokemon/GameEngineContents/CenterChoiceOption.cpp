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
	UIRenderer_ = CreateRenderer("ChoiceOption1.bmp");
	UIRenderer_->SetPivot({ 250, 30 });

	ArrowRenderer_ = CreateRenderer("ChoiceOption_Arrow.bmp");
	ArrowRenderer_->SetPivot({ 200, 0 });

	ArrowPos_.push_back({ 200, 0 });
	ArrowPos_.push_back({ 200, 60 });
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
		// Left 전환 후 포켓볼 -> Down 전환
		ParentText_->AddText("Thank you for waiting.");
		ParentText_->AddText("We've restored your POKEMON to");
		ParentText_->AddText("full health.");
		// Amin 후 다시 Down 전환
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
