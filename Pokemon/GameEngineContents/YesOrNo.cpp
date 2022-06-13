#include "YesOrNo.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

YesOrNo::YesOrNo() 
{
}

YesOrNo::~YesOrNo() 
{
}

void YesOrNo::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("YesOrNoSelect"))
	{
		GameEngineInput::GetInst()->CreateKey("YesOrNoUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("YesOrNoDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("YesOrNoClsoe", 'x');
		GameEngineInput::GetInst()->CreateKey("YesOrNoSelect", 'Z');
	}
}

void YesOrNo::Update()
{
	if (GameEngineInput::GetInst()->IsDown("YesOrNoUp"))
	{
		if (1 == Index_)
		{
			--Index_;
		}
	}
	
	else if (GameEngineInput::GetInst()->IsDown("YesOrNoDown"))
	{
		if (0 == Index_)
		{
			++Index_;
		}
	}

	else if (GameEngineInput::GetInst()->IsDown("YesOrNoClsoe"))
	{
		Off();
	}

	else if (GameEngineInput::GetInst()->IsDown("YesOrNoSelect"))
	{
		Off();
	}

	ShowArrow();
}


void YesOrNo::Init()
{
	Dialog_ = CreateRenderer("Yes.bmp");
	Dialog_->SetPivot(float4{ 310, 50 });
}

void YesOrNo::ShowArrow()
{
	if (0 == Index_)
	{
		Dialog_->SetImage("Yes.bmp");
	}

	else if (1 == Index_)
	{
		Dialog_->SetImage("No.bmp");
	}
}

