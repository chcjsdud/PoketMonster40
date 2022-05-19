#include "Bag.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

Bag::Bag() 
	: MyType_(BagType::ITEM)
	, BagRedrerer_(nullptr)
	, BagIndex_(0)
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
	LeftArrow_->SetPivot({-440, -20});
	LeftArrow_->SetOrder(-1);
	RightArrow_ = CreateRenderer("Bag_RightArrow.bmp");
	RightArrow_->SetPivot({ -200, -20 });
	UpArrow_ = CreateRenderer("Bag_UpArrow.bmp");
	UpArrow_->SetPivot({150, -290});
	UpArrow_->SetOrder(-1);
	DownArrow_ = CreateRenderer("Bag_DownArrow.bmp");
	DownArrow_->SetPivot({ 150, 90 });
	DownArrow_->SetOrder(-1);

	if (false == GameEngineInput::GetInst()->IsKey("LeftArrow"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftArrow", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("RightArrow", VK_RIGHT);
	}
}

void Bag::Update()
{
	MoveBag();

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

			--BagIndex_;
			MyType_ = static_cast<BagType>(BagIndex_);
		}
	}

	else if (true == GameEngineInput::GetInst()->IsDown("RightArrow"))
	{
		if (2 > BagIndex_)
		{
			IsMove_ = true;
			BagRedrerer_->PlusPivot({ 0, -15 });

			++BagIndex_;
			MyType_ = static_cast<BagType>(BagIndex_);
		}
	}
}

void Bag::ChangeBag()
{
	switch (MyType_)
	{
	case BagType::ITEM:
		BagRedrerer_->SetImage("Bag_LeftOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -40 });
		BagName_->SetImage("Bag_Items.bmp");

		LeftArrow_->SetOrder(-1);
		break;
		
	case BagType::KEYITEM:
		BagRedrerer_->SetImage("Bag_MiddleOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -48 });
		BagName_->SetImage("Bag_KeyItems.bmp");

		LeftArrow_->SetOrder(5);
		RightArrow_->SetOrder(5);
		break;

	case BagType::BALL:
		BagRedrerer_->SetImage("Bag_RightOpen.bmp");
		BagRedrerer_->SetPivot({ -317, -40 });
		BagName_->SetImage("Bag_PoketBalls.bmp");

		RightArrow_->SetOrder(-1);
		break;
	}
}
