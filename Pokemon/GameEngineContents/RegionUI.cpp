#include "RegionUI.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include <GameEngineBase/GameEngineInput.h>
#include "PlayerRed.h"
#include "ContentEnum.h"

RegionUI* RegionUI::Inst_;

RegionUI::RegionUI()
	: Fonts_(nullptr)
	, CurrentRegion_(WorldBackgroundSoundEnum::PalletTown)
	, NextRegion_(WorldBackgroundSoundEnum::None)
	, Renderer_(nullptr)
	, DisappearPos_()
	, AppearPos_()
	, LerpTimer_()
{
	Inst_ = this;
}

RegionUI::~RegionUI()
{
}

void RegionUI::ChangeRegion(WorldBackgroundSoundEnum _Enum)
{
	if (NextRegion_ == _Enum || CurrentRegion_ == _Enum)
	{
		return;
	}

	NextRegion_ = _Enum;
}

void RegionUI::NoneNamedRegion()
{
	CurrentRegion_ = WorldBackgroundSoundEnum::None;
	NextRegion_ = WorldBackgroundSoundEnum::None;
}

void RegionUI::Start()
{
	Fonts_ = GetLevel()->CreateActor<GameEngineContentFont>();
	Fonts_->SetOrder(static_cast<int>(RenderOrder::UI));
	Renderer_ = CreateRenderer("AreaUI.bmp", static_cast<int>(RenderOrder::UI));
	DisappearPos_ = { -220, -365 };
	AppearPos_ = {-220, -285};
	
	SetPosition(PlayerRed::MainRed_->GetPosition() + DisappearPos_);
	Fonts_->SetPosition(GetPosition() + float4(-100, -30));
	Fonts_->ShowString(" ", false);
	ChangeState(RegionState::Disappear);
}

void RegionUI::Update()
{
	StateUpdate();
	Fonts_->SetPosition(GetPosition() + float4(-100, -30));
}

////////////////// FSM
void RegionUI::ChangeState(RegionState _State)
{
	if (CurrentState_ == _State)
	{
		return;
	}

	CurrentState_ = _State;
	switch (_State)
	{
	case RegionState::Show:
		ShowStart();
		break;
	case RegionState::Hide:
		HideStart();
		break;
	case RegionState::Appear:
		AppearStart();
		break;
	case RegionState::Disappear:
		DisappearStart();
		break;
	default:
		break;
	}
}

void RegionUI::StateUpdate()
{
	switch (CurrentState_)
	{
	case RegionState::Show:
		ShowUpdate();
		break;
	case RegionState::Hide:
		HideUpdate();
		break;
	case RegionState::Appear:
		AppearUpdate();
		break;
	case RegionState::Disappear:
		DisappearUpdate();
		break;
	default:
		break;
	}
}

void RegionUI::ShowStart()
{
	LerpTimer_ = 0.0f;
}
void RegionUI::HideStart()
{
	LerpTimer_ = 0.0f;
}
void RegionUI::AppearStart()
{
	LerpTimer_ = 0.0f;
}
void RegionUI::DisappearStart()
{
	LerpTimer_ = 0.0f;
}

void RegionUI::ShowUpdate()
{
	LerpTimer_ += GameEngineTime::GetDeltaTime();
	SetPosition(PlayerRed::MainRed_->GetPosition() + float4::LerpLimit(DisappearPos_, AppearPos_, LerpTimer_ * 5.0f));
	Fonts_->SetPosition(GetPosition() + float4(-100, -30));

	if (LerpTimer_ >= 1.0f)
	{
		ChangeState(RegionState::Appear);
	}
}
void RegionUI::HideUpdate()
{
	LerpTimer_ += GameEngineTime::GetDeltaTime();
	SetPosition(PlayerRed::MainRed_->GetPosition() + float4::LerpLimit(AppearPos_, DisappearPos_, LerpTimer_ * 5.0f));
	Fonts_->SetPosition(GetPosition() + float4(-100, -30));

	if (LerpTimer_ >= 1.0f)
	{
		ChangeState(RegionState::Disappear);
	}
}
void RegionUI::AppearUpdate()
{
	LerpTimer_ += GameEngineTime::GetDeltaTime();
	SetPosition(PlayerRed::MainRed_->GetPosition() + AppearPos_);
	Fonts_->SetPosition(GetPosition() + float4(-100, -30));

	if (LerpTimer_ >= 1.2f || WorldBackgroundSoundEnum::None != NextRegion_)
	{
		ChangeState(RegionState::Hide);
	}
}
void RegionUI::DisappearUpdate()
{
	SetPosition(PlayerRed::MainRed_->GetPosition() + DisappearPos_);

	if (WorldBackgroundSoundEnum::None != NextRegion_)
	{
		Fonts_->ClearCurrentFonts();
		std::string TmpString = "";
		switch (NextRegion_)
		{
		case WorldBackgroundSoundEnum::PalletTown:
			TmpString = "PalletTown";
			break;
		case WorldBackgroundSoundEnum::Route1:
			TmpString = "Route1";
			break;
		case WorldBackgroundSoundEnum::ViridianCity:
			TmpString = "ViridianCity";
			break;
		case WorldBackgroundSoundEnum::Route22:
			TmpString = "Route22";
			break;
		case WorldBackgroundSoundEnum::Route2:
			TmpString = "Route2";
			break;
		case WorldBackgroundSoundEnum::PewterCity:
			TmpString = "PewterCity";
			break;
		default:
			break;
		}

		CurrentRegion_ = NextRegion_;
		NextRegion_ = WorldBackgroundSoundEnum::None;
		Fonts_->SetPosition(GetPosition() + float4(-100, -30));
		Fonts_->ShowString(TmpString, true);
		ChangeState(RegionState::Show);
	}
}
