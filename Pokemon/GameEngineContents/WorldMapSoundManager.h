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

// Ό³Έν :
class WorldMapSoundManager : public GameEngineActor
{
	static WorldMapSoundManager* Inst_;

public:
	static WorldMapSoundManager* GetInst()
	{
		return Inst_;
	}
	static void ChangeSound(WorldMapSoundEnum _Enum);
	static void StopSound();

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

private:
	static GameEngineSoundPlayer BgmPlayer_;
};

