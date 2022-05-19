#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentEnum.h"
#include <vector>

class Bag : public GameEngineActor
{
public:
	Bag();
	~Bag();

	Bag(const Bag& _Other) = delete;
	Bag(Bag&& _Other) noexcept = delete;
	Bag& operator=(const Bag& _Other) = delete;
	Bag& operator=(Bag&& _Other) noexcept = delete;

	void MoveBag(); //아이템 타입 이동
	void ChangeBag();

	void MoveItem(); //아이템 이동
	void ShowItemInfo();
	void ShowKeyItemInfo();
	void ShowBallInfo();

protected:
	void Start() override;
	void Update() override;

private:
	ItemType BagType_;

	class GameEngineRenderer* BagRedrerer_;
	GameEngineRenderer* BagName_;

	GameEngineRenderer* LeftArrow_;
	GameEngineRenderer* RightArrow_;
	GameEngineRenderer* UpArrow_;
	GameEngineRenderer* DownArrow_;

	GameEngineRenderer* SelectArrow_;
	int SelectIndex_;

	std::vector<class Item*> ItemList_;
	std::vector<Item*> KeyItemList_;
	std::vector<Item*> BallList_;

	GameEngineRenderer* ItemPreview_;

	std::vector<class GameEngineContentFont*> AllFonts_; 

	int BagIndex_;
	float MoveTime_;

	bool IsMove_;
};

