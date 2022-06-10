#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include "ContentEnum.h"

// Ό³Έν :
class WorldMapSoundManager : public GameEngineActor
{
private:
	static WorldMapSoundManager* Inst_;

public:
	static WorldMapSoundManager* GetInst()
	{
		return Inst_;
	}

	void PlayEffectSound(WorldSoundEffectEnum _Enum);
	void ChangeSound(WorldBackgroundSoundEnum _Enum);
	void StopSound();

	// constrcuter destructer
	WorldMapSoundManager();
	~WorldMapSoundManager();

	// delete Function
	WorldMapSoundManager(const WorldMapSoundManager& _Other) = delete;
	WorldMapSoundManager(WorldMapSoundManager&& _Other) noexcept = delete;
	WorldMapSoundManager& operator=(const WorldMapSoundManager& _Other) = delete;
	WorldMapSoundManager& operator=(WorldMapSoundManager&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineSoundPlayer BgmPlayer_;
	WorldBackgroundSoundEnum CurrentSoundState_;
	WorldBackgroundSoundEnum NextSoundState_;
};