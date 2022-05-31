#include "PokemonSummaryMenu.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "PlayerRed.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include "Pokemon.h"
#include "PokemonInfo.h"

PokemonSummaryMenu::PokemonSummaryMenu():
	TopMenuRenderer_(nullptr),
	CurState_(PokemonSummaryMenuType::PokemonInfo),
	PokemonFrameRenderer_(nullptr),
	PokemonInfoRenderer_(nullptr),
	IsOn_(false),
	CurrentOrder_(0),
	AccGravity_(0.0f),
	IsJumpStart_(false),
	CurYPos_(0),
	JumpTime_(0.0f)
{
	PokemonInfoList_.reserve(6);
	PokemonFrontRenderer_.reserve(6);
	LevelFonts_.reserve(6);
	AllFonts_.reserve(60);
	NumberFonts_.reserve(6);
}

PokemonSummaryMenu::~PokemonSummaryMenu()
{
}

void PokemonSummaryMenu::InitPokemonSummaryMenu(int _PokemonOrder)
{
	CurrentOrder_ = _PokemonOrder;
	GetPlayerPokemon();
	InitRenderer_();
	InitFonts_();

	//필요한 것만 On
	PokemonFrontRenderer_[CurrentOrder_]->On();
	PokemonJumpStart();
	IsOn_ = true;
}

void PokemonSummaryMenu::GetPlayerPokemon()
{
	for (Pokemon* i : PlayerRed::MainRed_->GetPokemonList())
	{
		PokemonInfoList_.push_back(i->GetInfo());
	}
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
	PokemonJump();
	UpdateState();
}

void PokemonSummaryMenu::Render()
{
	for (size_t i = 0; i < PokemonInfoList_.size(); i++)
	{
		if (i != CurrentOrder_)
		{
			PokemonFrontRenderer_[i]->Off();
			LevelFonts_[i]->Off();
			NameFonts_[i]->Off();
			NumberFonts_[i]->Off();
		}
		else
		{
			PokemonFrontRenderer_[i]->On();
			LevelFonts_[i]->On();
			NameFonts_[i]->On();
			NumberFonts_[i]->On();
		}
	}
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
	for (size_t i = 0; i < PokemonInfoList_.size(); i++)
	{
		GameEngineRenderer* NewRenderer = CreateRenderer(PokemonInfoList_[i]->GetMyBattleFront(), GetOrder(), RenderPivot::LeftTop,{120,120});
		NewRenderer->SetTransColor(RGB(255, 0, 255));
		NewRenderer->Off();
		PokemonFrontRenderer_.push_back(NewRenderer);
	}



}

void PokemonSummaryMenu::InitFonts_()
{
	//넘버 폰트
	{
		for (size_t i = 0; i < PokemonInfoList_.size(); i++)
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder());
			NewFonts->SetPosition(GetPosition() + float4(660, 84));
			NewFonts->ShowString("00"+std::to_string(i), true);
			NewFonts->Off();
			NumberFonts_.push_back(NewFonts);
			AllFonts_.push_back(NewFonts);
		}
	}
	//레벨 폰트
	for (size_t i = 0; i < PokemonInfoList_.size(); i++)
	{
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder());
			NewFonts->SetPosition(GetPosition()+float4(10,70));
			NewFonts->ShowString("Lv " + std::to_string(PokemonInfoList_[i]->GetMyLevel()), true);
			NewFonts->Off();
			LevelFonts_.push_back(NewFonts);
			AllFonts_.push_back(NewFonts);
		}
	}

	//이름 폰트
	for (size_t i = 0; i < PokemonInfoList_.size(); i++)
	{
		{
			GameEngineContentFont* NewFonts = GetLevel()->CreateActor<GameEngineContentFont>(GetOrder());
			NewFonts->SetPosition(GetPosition() + float4(660, 140));
			NewFonts->ShowString(PokemonInfoList_[i]->GetNameCopy(), true);
			NewFonts->Off();
			NameFonts_.push_back(NewFonts);
			AllFonts_.push_back(NewFonts);
		}
	}
}

void PokemonSummaryMenu::DestroyPokemonSummaryMenu()
{
	for (GameEngineContentFont* i : AllFonts_)
	{
		i->ClearCurrentFonts();
	}
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
		DestroyPokemonSummaryMenu();
		Off();
	}

	if (GameEngineInput::GetInst()->IsDown("Up") == true)
	{
		if (CurrentOrder_ <= 0)
		{
			return;
		}
		PokemonJumpStart();
		CurrentOrder_--;
	}

	if (GameEngineInput::GetInst()->IsDown("Down") == true)
	{
		if (CurrentOrder_ >= PokemonInfoList_.size() - 1)
		{
			return;
		}
		PokemonJumpStart();
		CurrentOrder_++;
	}
}

void PokemonSummaryMenu::PokemonJump()
{
	if (IsJumpStart_ == true)
	{
		JumpTime_ += GameEngineTime::GetDeltaTime();
		if (JumpTime_ > 0.5f)
		{
			CurYPos_ = 0;
			AccGravity_ = 0;
			JumpTime_ = 0;
			IsJumpStart_ = false;
		}

		CurYPos_ += AccGravity_ *GameEngineTime::GetDeltaTime();

		if (CurYPos_ > 20.0f)
		{
			AccGravity_ -= 10000 * GameEngineTime::GetDeltaTime();
		}
		else
		{
			AccGravity_ += 10000 * GameEngineTime::GetDeltaTime();
		}

		PokemonFrontRenderer_[CurrentOrder_]->SetPivot({ 120,120 - CurYPos_ });
	}
	else
	{
		PokemonFrontRenderer_[CurrentOrder_]->SetPivot({ 120,120 });
	}
}

void PokemonSummaryMenu::PokemonJumpStart()
{
	IsJumpStart_ = true;
	PokemonFrontRenderer_[CurrentOrder_]->SetPivot({ 120,120 });
	CurYPos_ = 0;
	AccGravity_ = 0;
	JumpTime_ = 0;
}
