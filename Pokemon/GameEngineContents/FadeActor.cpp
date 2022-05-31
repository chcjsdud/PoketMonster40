#include "FadeActor.h"
#include <GameEngine/GameEngineRenderer.h>


FadeActor::FadeActor() 
	: Background_(nullptr)
	, Alpha_(0.0f)
	, FadeIn_(false)
	, Fadeout_(false)
	, IsChange_(false)
{
}

FadeActor::~FadeActor() 
{
}

//void (*Ptr_)();

void FadeActor::FadeIn(/*void (*Ptr)()*/)
{
	FadeIn_ = true;
	Fadeout_ = false;
}

void FadeActor::FadeOut()
{
	Alpha_ = 255;
	Background_->SetAlpha(255);

	Fadeout_ = true;
	FadeIn_ = false;
}

void FadeActor::Start()
{
	Background_ = CreateRenderer("FadeInOut.bmp", 100);
	Background_->SetAlpha(0);
}

void FadeActor::Update()
{
	//페이드 인
	if (true == FadeIn_
		&& false == Fadeout_)
	{
		Alpha_ += GameEngineTime::GetDeltaTime() * 500.f;
		Background_->SetAlpha(static_cast<int>(Alpha_));

		if (255 <= Alpha_)
		{
			FadeOut();
			Alpha_ = 255.0f;
		}
	}

	//페이드 아웃
	else if (true == Fadeout_
		&& false == FadeIn_)
	{
		Alpha_ -= GameEngineTime::GetDeltaTime() * 500.f;
		Background_->SetAlpha(static_cast<int>(Alpha_));

		if (0 >= Alpha_)
		{
			FadeIn_ = false;
			Fadeout_ = false;
			IsChange_ = true;

			Alpha_ = 0.f;
			Background_->SetAlpha(static_cast<int>(Alpha_));

			Background_->SetAlpha(0);
		}
	}
}

