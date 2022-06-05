#include "WorldMapSoundManager.h"

WorldMapSoundManager* WorldMapSoundManager::Inst_;
GameEngineSoundPlayer WorldMapSoundManager::BgmPlayer_;

WorldMapSoundManager::WorldMapSoundManager() 
{
}

WorldMapSoundManager::~WorldMapSoundManager() 
{
}

void WorldMapSoundManager::Start()
{
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
	switch (_Enum)
	{
	case WorldMapSoundEnum::PalletTown:
		BgmPlayer_.StopWithNullCheck();
		BgmPlayer_ = GameEngineSound::SoundPlayControl("World_PalletTown.mp3");
		BgmPlayer_.Volume(0.5f);
		break;
	case WorldMapSoundEnum::Route1:
		BgmPlayer_.StopWithNullCheck();
		BgmPlayer_ = GameEngineSound::SoundPlayControl("World_Route1.mp3");
		BgmPlayer_.Volume(0.5f);
		break;
	default:
		break;
	}
}

void WorldMapSoundManager::StopSound()
{
	BgmPlayer_.StopWithNullCheck();
}