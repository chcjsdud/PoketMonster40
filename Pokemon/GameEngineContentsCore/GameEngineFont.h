#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineActor.h>
#include <list>
#include <string>

// Ό³Έν :
class GameEngineFont : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEngineFont();
	~GameEngineFont();

	// delete Function
	GameEngineFont(const GameEngineFont& _Other) = delete;
	GameEngineFont(GameEngineFont&& _Other) noexcept = delete;
	GameEngineFont& operator=(const GameEngineFont& _Other) = delete;
	GameEngineFont& operator=(GameEngineFont&& _Other) noexcept = delete;

	void Destroy();
	
	
protected:
	void Update() override;
	void Start() override;
	void Render() override {}

private:
	float4 FirstCharPos_;
	float WaitTime_;

	std::string Word_;

	static std::list<GameEngineFont*> AllFonts_;
	static
};

