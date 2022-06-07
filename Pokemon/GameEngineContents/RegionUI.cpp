#include "RegionUI.h"
#include <GameEngineContentsCore/GameEngineContentFont.h>
#include <GameEngineBase/GameEngineInput.h>

RegionUI* RegionUI::Inst_;

RegionUI::RegionUI()
	: Fonts_(nullptr)
	, CurrentRegion_()
	, NextRegion_()
	, StartPos_()
	, GoalPos_()
	, LerpTimer_()
	, IsShow_()
	, IsHide_()
	, IsShowing_()
{
	Inst_ = this;
	GameEngineInput::GetInst()->CreateKey("JBMTest2", 'I');
	GameEngineInput::GetInst()->CreateKey("JBMTest3", 'O');

	//Fonts_ = GetLevel()->CreateActor<GameEngineContentFont>();
	//Fonts_->ShowString(" ", true);
}

RegionUI::~RegionUI()
{
}

void RegionUI::ChangeRegion(WorldBackgroundSoundEnum _Enum)
{
	if (CurrentRegion_ == _Enum || NextRegion_ == _Enum)
	{
		return;
	}

	Hide();

	NextRegion_ = _Enum;
	Fonts_->ClearCurrentFonts();
	std::string TmpString = "";
	switch (_Enum)
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

	Fonts_->ShowString(TmpString, true);
	Show();
}

void RegionUI::Start()
{
}

void RegionUI::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("JBMTest2"))
	{
		ChangeRegion(WorldBackgroundSoundEnum::Route1);
	}
	if (true == GameEngineInput::GetInst()->IsDown("JBMTest3"))
	{
		ChangeRegion(WorldBackgroundSoundEnum::PalletTown);
	}

	if (NextRegion_ == WorldBackgroundSoundEnum::None)
	{
		return;
	}

	if (true == IsShow_)
	{
		LerpTimer_ += GameEngineTime::GetDeltaTime();
		SetPosition(float4::LerpLimit(StartPos_, GoalPos_, LerpTimer_));

		if (LerpTimer_ >= 1.0f)
		{
			IsShow_ = false;
		}
	}
	else if (true == IsHide_)
	{
		LerpTimer_ += GameEngineTime::GetDeltaTime();
		SetPosition(float4::LerpLimit(GoalPos_, StartPos_, LerpTimer_));
		if (LerpTimer_ >= 1.0f)
		{
			IsHide_ = true;
		}
	}

	/*float TmpValue = 0.0f;
	BgmPlayer_.GetVolume(&TmpValue);
	if (TmpValue < 0.05f)
	{
		CurrentSoundState_ = NextSoundState_;
		NextSoundState_ = WorldBackgroundSoundEnum::None;

		switch (CurrentSoundState_)
		{
		case WorldBackgroundSoundEnum::PalletTown:
			BgmPlayer_.StopWithNullCheck();
			BgmPlayer_ = GameEngineSound::SoundPlayControl("World_PalletTown.mp3");
			BgmPlayer_.SetVolume(0.5f);
			break;
		case WorldBackgroundSoundEnum::Route1:
			BgmPlayer_.StopWithNullCheck();
			BgmPlayer_ = GameEngineSound::SoundPlayControl("World_Route1.mp3");
			BgmPlayer_.SetVolume(0.5f);
			break;
		case WorldBackgroundSoundEnum::ViridianCity:
			break;
		default:
			break;
		}
	}
	else
	{
		BgmPlayer_.SetVolume(TmpValue - GameEngineTime::GetDeltaTime());
	}*/
}

void RegionUI::Show()
{
	LerpTimer_ = 0.0f;
	IsShow_ = true;
}

void RegionUI::Hide()
{
	LerpTimer_ = 0.0f;
	IsHide_ = true;
}