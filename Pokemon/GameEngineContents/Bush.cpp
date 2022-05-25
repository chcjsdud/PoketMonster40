#include "Bush.h"

Bush::Bush() 
	: Renderer_(nullptr)
	, NextTimer_(0.0f)
{
}

Bush::~Bush() 
{
}

void Bush::Start()
{
	Renderer_ = CreateRenderer("Bush.bmp", 1);
}

void Bush::CreateEffect()
{
	GameEngineRenderer* TmpRenderer_ = CreateRenderer();
	TmpRenderer_->CreateAnimation("BushEffect.bmp", "BushEffect", 0, 3, 0.1f, false);
	TmpRenderer_->ChangeAnimation("BushEffect");
	TmpRenderer_->Death(0.4f);
}
