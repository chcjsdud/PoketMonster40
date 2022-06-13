#include "WorldMapSoundManager.h"
#include "PlayerRed.h"

WorldMapSoundManager* WorldMapSoundManager::Inst_;

WorldMapSoundManager::WorldMapSoundManager()
	: CurrentSoundState_(WorldBackgroundSoundEnum::None)
	, NextSoundState_(WorldBackgroundSoundEnum::None)
{
	Inst_ = this;
}

WorldMapSoundManager::~WorldMapSoundManager()
{
}

void WorldMapSoundManager::Start()
{
}

void WorldMapSoundManager::Update()
{
	if (NextSoundState_ == WorldBackgroundSoundEnum::None)
	{
		return;
	}

	float TmpValue = 0.0f;
	BgmPlayer_.GetVolume(&TmpValue);
	if (TmpValue < 0.05f)
	{
		CurrentSoundState_ = NextSoundState_;
		NextSoundState_ = WorldBackgroundSoundEnum::None;

		BgmPlayer_.StopWithNullCheck();
		switch (CurrentSoundState_)
		{
		case WorldBackgroundSoundEnum::PalletTown:
			BgmPlayer_ = GameEngineSound::SoundPlayControl("World_PalletTown.mp3");
			BgmPlayer_.SetVolume(0.5f);
			break;
		case WorldBackgroundSoundEnum::Route1:
		case WorldBackgroundSoundEnum::Route22:
		case WorldBackgroundSoundEnum::Route2:
			BgmPlayer_ = GameEngineSound::SoundPlayControl("World_Route1.mp3");
			BgmPlayer_.SetVolume(0.5f);
			break;
		case WorldBackgroundSoundEnum::ViridianCity:
		case WorldBackgroundSoundEnum::PewterCity:
			BgmPlayer_ = GameEngineSound::SoundPlayControl("World_ViridianCity.mp3");
			BgmPlayer_.SetVolume(0.2f);
			break;
		case WorldBackgroundSoundEnum::OakLap:
			BgmPlayer_ = GameEngineSound::SoundPlayControl("World_OakLap.mp3");
			BgmPlayer_.SetVolume(0.2f);
			break;
		case WorldBackgroundSoundEnum::Gym:
			BgmPlayer_ = GameEngineSound::SoundPlayControl("World_Gym.mp3");
			BgmPlayer_.SetVolume(0.2f);
			break;
		default:
			break;
		}
	}
	else
	{
		BgmPlayer_.SetVolume(TmpValue - GameEngineTime::GetDeltaTime());
	}
}

void WorldMapSoundManager::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void WorldMapSoundManager::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	WorldMapSoundManager::GetInst()->StopSound();
}

void WorldMapSoundManager::PlayEffectSound(WorldSoundEffectEnum _Enum)
{
	switch (_Enum)
	{
	case WorldSoundEffectEnum::Block:
		GameEngineSound::SoundPlayOneShotWithVolume("World_Block.wav", 0.5f);
		break;
	case WorldSoundEffectEnum::Click:
		GameEngineSound::SoundPlayOneShotWithVolume("World_Click.wav", 0.5f);
		break;
	case WorldSoundEffectEnum::Menu:
		GameEngineSound::SoundPlayOneShotWithVolume("World_Menu.wav", 0.5f);
		break;
	default:
		break;
	}
}

void WorldMapSoundManager::ChangeSound(WorldBackgroundSoundEnum _Enum)
{
	if (true == PlayerRed::MainRed_->GetStartBattle())
	{
		return;
	}
	if (CurrentSoundState_ == _Enum || NextSoundState_ == _Enum)
	{
		return;
	}

	NextSoundState_ = _Enum;
}

void WorldMapSoundManager::StopSound()
{
	CurrentSoundState_ = WorldBackgroundSoundEnum::None;
	NextSoundState_ = WorldBackgroundSoundEnum::None;
	BgmPlayer_.StopWithNullCheck();
}