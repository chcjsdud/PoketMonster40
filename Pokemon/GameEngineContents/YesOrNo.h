#pragma once
#include "GameEngine/GameEngineActor.h"	

// Ό³Έν :
class YesOrNo : public GameEngineActor
{
public:
	// constrcuter destructer
	YesOrNo();
	~YesOrNo();

	// delete Function
	YesOrNo(const YesOrNo& _Other) = delete;
	YesOrNo(YesOrNo&& _Other) noexcept = delete;
	YesOrNo& operator=(const YesOrNo& _Other) = delete;
	YesOrNo& operator=(YesOrNo&& _Other) noexcept = delete;

	void Init();
	void ShowArrow();

protected:
	void Start() override;
	void Update() override;

private:
	class GameEngineRenderer* Dialog_;

	int Index_;
};

