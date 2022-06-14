#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class CenterAnimationUI : public GameEngineActor
{
public:
	// constrcuter destructer
	CenterAnimationUI();
	~CenterAnimationUI();

	// delete Function
	CenterAnimationUI(const CenterAnimationUI& _Other) = delete;
	CenterAnimationUI(CenterAnimationUI&& _Other) noexcept = delete;
	CenterAnimationUI& operator=(const CenterAnimationUI& _Other) = delete;
	CenterAnimationUI& operator=(CenterAnimationUI&& _Other) noexcept = delete;

	void MakeBalls(int _Count);

protected:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* LeftRenderer_;
	GameEngineRenderer* UpRenderer_;
	std::vector<GameEngineRenderer*> LeftBallRenderers_;

};

