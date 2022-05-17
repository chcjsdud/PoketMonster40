#include "PokemonMenu.h"
#include "UIEnum.h"
#include <GameEngine/GameEngineRenderer.h>

PokemonMenu::PokemonMenu():
	BackgroundRenderer_(nullptr)
{
}

PokemonMenu::~PokemonMenu()
{
}

void PokemonMenu::Start()
{
	BackgroundRenderer_ = CreateRenderer(static_cast<int>(UIRenderType::Background), RenderPivot::LeftTop);
	BackgroundRenderer_->SetImage("PoketmonMenu_22.bmp");

	BoxRenderer_[0] = CreateRenderer(static_cast<int>(UIRenderType::Box), RenderPivot::LeftTop,{8,80});
	BoxRenderer_[0]->SetImage("PoketmonMenu_14.bmp");

	for (int i = 0; i < 6; i++)
	{
		BoxRenderer_[0]->SetTransColor(RGB(255, 0, 255));
	}

}

void PokemonMenu::Update()
{

}

void PokemonMenu::Render()
{
}


