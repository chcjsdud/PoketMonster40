#include "WorldMapSoundManager.h"

WorldMapSoundManager* WorldMapSoundManager::Inst_;

WorldMapSoundManager::WorldMapSoundManager() 
	: CurrentSoundState_(WorldMapSoundEnum::None)
	, NextSoundState_(WorldMapSoundEnum::None)
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
	if (NextSoundState_ != WorldMapSoundEnum::None)
	{
		float TmpValue = 0.0f;
		BgmPlayer_.GetVolume(&TmpValue);
		if (TmpValue < 0.05f)
		{
			CurrentSoundState_ = NextSoundState_;
			NextSoundState_ = WorldMapSoundEnum::None;

			switch (CurrentSoundState_)
			{
			case WorldMapSoundEnum::PalletTown:
				BgmPlayer_.StopWithNullCheck();
				BgmPlayer_ = GameEngineSound::SoundPlayControl("World_PalletTown.mp3");
				BgmPlayer_.SetVolume(0.5f);
				break;
			case WorldMapSoundEnum::Route1:
				BgmPlayer_.StopWithNullCheck();
				BgmPlayer_ = GameEngineSound::SoundPlayControl("World_Route1.mp3");
				BgmPlayer_.SetVolume(0.5f);
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

void WorldMapSoundManager::ChangeSound(WorldMapSoundEnum _Enum)
{
	if (CurrentSoundState_ == _Enum || NextSoundState_ == _Enum)
	{
		return;
	}
	NextSoundState_ = _Enum;
}

void WorldMapSoundManager::StopSound()
{
	BgmPlayer_.StopWithNullCheck();
}