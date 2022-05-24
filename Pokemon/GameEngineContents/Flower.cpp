#include "Flower.h"

Flower::Flower() 
	: Renderer_(nullptr)
{
}

Flower::~Flower() 
{
}

void Flower::Start()
{
	Renderer_ = CreateRenderer();
	Renderer_->CreateAnimation("Flower.bmp", "Idle", 0, 4, 0.1f, true);
	Renderer_->ChangeAnimation("Idle");
	Renderer_->SetPivot({-2, 1});
}
