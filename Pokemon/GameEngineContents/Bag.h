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
	void ShowItemList();
	void ShowKeyItemList();
	void ShowBallList();

	void MoveItem(); //아이템 이동
	void MoveSelectArrow();
	void ShowItemInfo(); //현재 선택한 아이템의 정보
	void ShowKeyItemInfo();
	void ShowBallInfo();

	void UpFonts(); //아이템이 5개 이상일 경우 폰트 움직임
	void DownFonts();
	void HideFonts();
	void ShowFonts(std::vector<class Item*>& _Fonts);
	void DestroyFonts(); //전체 폰트 삭제
	void DestroyNameFonts(); //아이템 이름 삭제
	void DestroyDescFonts(); //아이템 내용 삭제
	void DestroyOverlapFonts(); //아이템 중복 삭제


protected:
	void Start() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	ItemType BagType_;

	class GameEngineRenderer* BagRedrerer_;
	GameEngineRenderer* BagName_;
	GameEngineRenderer* BagDialog_;

	GameEngineRenderer* LeftArrow_;
	GameEngineRenderer* RightArrow_;
	GameEngineRenderer* UpArrow_;
	GameEngineRenderer* DownArrow_;

	GameEngineRenderer* SelectArrow_; //아이템 선택 화살표
	int SelectIndex_;

	std::vector<Item*> ItemList_;
	std::vector<Item*> KeyItemList_;
	std::vector<Item*> BallList_;

	GameEngineRenderer* ItemPreview_; //현재 선택한 아이템 이미지

	std::vector<class GameEngineContentFont*> ItemNameFonts_; 
	std::vector<class GameEngineContentFont*> ItemDescFonts_;
	std::vector<class GameEngineContentFont*> ItemOverlapFonts_;

	int BagIndex_; //가방 순서

	//가방 움직임
	float BagMoveTime_;
	bool IsMove_;

	//화살표 움직임
	float ArrowMoveTime_;
	bool IsArrowSync_;
};

