#pragma once
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <list>
#include <string>
#include <queue>

// 설명 :
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
	
	// 다음 문장 출력 함수
	// 
	// True  : 다음 문장이 있고 출력 중 (혹은 예정)
	// False : 다음 문장이 없음
	bool NextString()
	{

	}
protected:
	void Update() override;
	void Start() override;
	void Render() override {}

private:
	float4 CurrentPivot_;
	float OriginalWaitTime_;
	float CurrentWaitTime_;
	int StringRow_;

	// 키 푸시 대기
	bool WatingKeyPush_;
	//


	std::queue<std::string> StringQueue_;

	std::string CurrentString_;
	std::string CurrentWord_;
	static std::list<GameEngineContentFont*> AllFonts_;
};