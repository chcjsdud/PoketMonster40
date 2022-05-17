#pragma once
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineActor.h>
#include <list>
#include <string>

// Ό³Έν :
class GameEngineContentFont : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEngineContentFont();
	~GameEngineContentFont();

	// delete Function
	GameEngineContentFont(const GameEngineContentFont& _Other) = delete;
	GameEngineContentFont(GameEngineContentFont&& _Other) noexcept = delete;
	GameEngineContentFont& operator=(const GameEngineContentFont& _Other) = delete;
	GameEngineContentFont& operator=(GameEngineContentFont&& _Other) noexcept = delete;

	void Destroy();
	bool ShowString(const std::string& _String, float _WaitTime = 0.01f);
	inline void SetPostion(const float4& _Pos)
	{
		FirstCharPos_ = _Pos;
	}
	
protected:
	void Update() override;
	void Start() override;
	void Render() override {}

private:
	float4 FirstCharPos_;
	float WaitTime_;
	int CurrentWord_;

	std::string StringQueue_;

	static std::list<GameEngineContentFont*> AllFonts_;
};

