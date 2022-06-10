#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

// Ό³Έν :
class ShopChoiceOption : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopChoiceOption();
	~ShopChoiceOption();

	// delete Function
	ShopChoiceOption(const ShopChoiceOption& _Other) = delete;
	ShopChoiceOption(ShopChoiceOption&& _Other) noexcept = delete;
	ShopChoiceOption& operator=(const ShopChoiceOption& _Other) = delete;
	ShopChoiceOption& operator=(ShopChoiceOption&& _Other) noexcept = delete;

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

	class Shop* Shop_;
};

