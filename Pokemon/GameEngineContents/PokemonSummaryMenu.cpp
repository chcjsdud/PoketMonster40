#include "PokemonSummaryMenu.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

PokemonSummaryMenu::PokemonSummaryMenu():
	TopMenuRenderer_(nullptr),
	CurState_(PokemonSummaryMenuType::PokemonInfo),
	PokemonFrameRenderer_(nullptr)
{
}

PokemonSummaryMenu::~PokemonSummaryMenu()
{
}

void PokemonSummaryMenu::Start()
{
	InitRenderer_();

}

void PokemonSummaryMenu::Update()
{
	UpdateState();
}

void PokemonSummaryMenu::InitRenderer_()
{
	TopMenuRenderer_ = CreateRenderer("PokemonInfo.bmp", GetOrder(), RenderPivot::LeftTop);
	TopMenuRenderer_->SetTransColor(RGB(255, 0, 255));

	PokemonFrameRenderer_ = CreateRenderer("Pokemon_Frame.bmp", GetOrder(), RenderPivot::LeftTop,{0,64});
	PokemonFrameRenderer_->SetTransColor(RGB(255, 0, 255));
}

void PokemonSummaryMenu::InitFonts_()
{
}

void PokemonSummaryMenu::ChangeState(PokemonSummaryMenuType _State)
{
	if (_State == CurState_)
	{
		return;
	}
	switch (_State)
	{
	case PokemonSummaryMenu::PokemonSummaryMenuType::PokemonInfo:
		PokemonInfoStart();
		break;
	default:
		break;
	}

	CurState_ = _State;
}

void PokemonSummaryMenu::UpdateState()
{
	switch (CurState_)
	{
	case PokemonSummaryMenu::PokemonSummaryMenuType::PokemonInfo:
		PokemonInfoUpdate();
		break;

	default:
		break;
	}
}

void PokemonSummaryMenu::PokemonInfoStart()
{

}

void PokemonSummaryMenu::PokemonInfoUpdate()
{
	if (GameEngineInput::GetInst()->IsDown("X") == true)
	{
		//
		Off();
	}
}
