#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>

// 설명 :
class WorldMapBackground : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMapBackground();
	~WorldMapBackground();

	// delete Function
	WorldMapBackground(const WorldMapBackground& _Other) = delete;
	WorldMapBackground(WorldMapBackground&& _Other) noexcept = delete;
	WorldMapBackground& operator=(const WorldMapBackground& _Other) = delete;
	WorldMapBackground& operator=(WorldMapBackground&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* WorldMap1_;
	GameEngineRenderer* RoomsRenderer_;
	GameEngineRenderer* TestRenderer_;
	std::vector<float4> AllPosVector;
	// 0 == 시작지점
	// 1 == 시작지점 올라왔을때 위치
	// 2 == 시작지점 내려갔을때 위치

	void Start() override;
	void Update() override;
};

