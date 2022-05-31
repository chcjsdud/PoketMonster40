#include "PokemonSummaryMenu.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

PokemonSummaryMenu::PokemonSummaryMenu():
	TopMenuRenderer_(nullptr),
	CurState_(PokemonSummaryMenuType::PokemonInfo),
	PokemonFrameRenderer_(nullptr),
	PokemonInfoRenderer_(nullptr),
	IsOn_(false),
	PokemonInfo_(nullptr)
{
}

PokemonSummaryMenu::~PokemonSummaryMenu()
{
}

void PokemonSummaryMenu::InitPokemonSummaryMenu(int _PokemonOrder)
{
	//PokemonInfo_ = _Info;
	InitRenderer_();
	IsOn_ = true;
}

void PokemonSummaryMenu::Start()
{

}

void PokemonSummaryMenu::Update()
{
	if (IsOn_ == false)
	{
		return;
	}
	UpdateState();
}

void PokemonSummaryMenu::InitRenderer_()
{
	//기본 백그라운드 
	TopMenuRenderer_ = CreateRenderer("PokemonInfo.bmp", GetOrder(), RenderPivot::LeftTop);
	TopMenuRenderer_->SetTransColor(RGB(255, 0, 255));

	PokemonFrameRenderer_ = CreateRenderer("Pokemon_Frame.bmp", GetOrder(), RenderPivot::LeftTop,{0,64});
	PokemonFrameRenderer_->SetTransColor(RGB(255, 0, 255));

	PokemonInfoRenderer_ = CreateRenderer("PokemonInfo_Window.bmp", GetOrder(), RenderPivot::LeftTop, { 0,64 });
	PokemonInfoRenderer_->SetTransColor(RGB(255, 0, 255));

	//포켓몬 앞판

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
