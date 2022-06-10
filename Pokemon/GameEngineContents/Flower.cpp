#include "Flower.h"
#include "ContentEnum.h"

Flower::Flower() 
	: Renderer_(nullptr)
{
}

Flower::~Flower() 
{
}

void Flower::Start()
{
	Renderer_ = CreateRenderer(static_cast<int>(RenderOrder::Background));
	Renderer_->CreateAnimation("Flower.bmp", "Idle", 0, 4, 0.27f, true);
	Renderer_->ChangeAnimation("Idle");
	Renderer_->SetPivot({-2, 1});
}
