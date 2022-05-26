#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

class CenterChoiceOption : public GameEngineActor
{
public:
	// constrcuter destructer
	CenterChoiceOption();
	~CenterChoiceOption();

	// delete Function
	CenterChoiceOption(const CenterChoiceOption& _Other) = delete;
	CenterChoiceOption(CenterChoiceOption&& _Other) noexcept = delete;
	CenterChoiceOption& operator=(const CenterChoiceOption& _Other) = delete;
	CenterChoiceOption& operator=(CenterChoiceOption&& _Other) noexcept = delete;

	void SetParent(class InteractionText* _Parent);

protected:

private:
	std::vector<float4> ArrowPos_;
	GameEngineRenderer* UIRenderer_;
	GameEngineRenderer* ArrowRenderer_;
	class InteractionText* ParentText_;
	int CurrentIndex_;

	void Start() override;
	void Update() override;
	void SelectIndex();
};

