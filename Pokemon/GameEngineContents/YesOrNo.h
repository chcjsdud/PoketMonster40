#pragma once
#include "GameEngine/GameEngineActor.h"	
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

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

	void SetParent(class InteractionText* _Parent);

protected:
	void Start() override;
	void Update() override;
	void SelectIndex();

private:
	std::vector<float4> ArrowPos_;
	GameEngineRenderer* UIRenderer_;
	GameEngineRenderer* ArrowRenderer_;
	class InteractionText* Dialog_;
	int Index_;
};

