#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class Item : public GameEngineActor
{
public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	inline void SetValue(int _Value)
	{
		Value_ = _Value;
	}

	inline int GetValue()
	{
		return Value_;
	}

	inline void SetIcon(GameEngineRenderer* _Image)
	{
		Icon_ = _Image;
	}

	inline GameEngineRenderer* GetIcon()
	{
		return Icon_;
	}

protected:

private:
	int Value_; //상처약일 때 회복될 수치
	GameEngineRenderer* Icon_;

	void Start() override;
	void Update() override;

};

