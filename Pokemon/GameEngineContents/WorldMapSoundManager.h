#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

enum class WorldMapSoundEnum
{
	None,
	PalletTown,
	Route1,
	Max
};

enum class WorldSoundEffectEnum
{
	None,
	Block,
	Click,
	Menu,
	Max
};

// Ό³Έν :
class WorldMapSoundManager : public GameEngineActor
{
	static WorldMapSoundManager* Inst_;

public:
	static WorldMapSoundManager* GetInst()
	{
		return Inst_;
	}

	void PlayEffectSound(WorldSoundEffectEnum _Enum);
	void ChangeSound(WorldMapSoundEnum _Enum);
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

private:
	GameEngineSoundPlayer BgmPlayer_;
	WorldMapSoundEnum CurrentSoundState_;
	WorldMapSoundEnum NextSoundState_;

};