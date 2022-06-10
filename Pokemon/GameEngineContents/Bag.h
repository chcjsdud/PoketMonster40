#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentEnum.h"
#include <vector>
#include "Item.h"

enum class BagState
{
	ListMenu,
	DialogMenu,
	ItemUse,
	ItemGive,
	ItemToss
};

class Bag : public GameEngineActor
{
public:
	Bag();
	~Bag();

	Bag(const Bag& _Other) = delete;
	Bag(Bag&& _Other) noexcept = delete;
	Bag& operator=(const Bag& _Other) = delete;
	Bag& operator=(Bag&& _Other) noexcept = delete;

	void BagInit();
	void DestroyBag();

	void MoveBag(); //아이템 타입 이동
	void MoveArrow();
	void ChangeBag();
	void ShowItemList();
	void ShowKeyItemList();
	void ShowBallList();

	void MoveItem(); //아이템 이동
	void MoveSelectArrow();
	void ShowItemInfo(std::vector<Item*>& _List); //현재 선택한 아이템의 정보

	void ActiveDialog(); //다이얼로그 활성화 체크
	void MoveDialog();
	void SelectDialog();
	void OnDialog();
	void CloseDialog();

	void UpFonts(); //아이템이 5개 이상일 경우 폰트 움직임
	void DownFonts();
	void HideFonts();
	void ShowFonts(std::vector<Item*>& _List);
	void DestroyFonts(); //전체 폰트 삭제
	void DestroyNameFonts(); //아이템 이름 삭제
	void DestroyDescFonts(); //아이템 내용 삭제
	void DestroyOverlapFonts(); //아이템 중복 삭제
	void DestroyDialogFonts(); //다이얼로그 삭제

	void Use(std::vector<Item*>& _List);
	void Give(std::vector<Item*>& _List);
	void Toss(std::vector<Item*>& _List);

	inline void SetCurrentPokemon(class Pokemon* _Pokemon)
	{
		CurrentPokemon_ = _Pokemon;
	}

	inline void SetPlayerItemList(std::vector<Item*>& _List)
	{
		for (int i = 0; i < _List.size(); ++i)
		{
			if (ItemType::ITEM == _List[i]->GetInfo()->GetType())
			{
				ItemList_.push_back(_List[i]);
			}
			
			else if (ItemType::KEYITEM == _List[i]->GetInfo()->GetType())
			{
				KeyItemList_.push_back(_List[i]);
			}

			else if (ItemType::BALL == _List[i]->GetInfo()->GetType())
			{
				BallList_.push_back(_List[i]);
			}
		}
	}

protected:
	void Start() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	ItemType BagType_;
	BagState BagState_;

	class FadeActor* FadeActor_;

	class GameEngineRenderer* BagRedrerer_;
	GameEngineRenderer* Title_;
	GameEngineRenderer* BagName_;
	GameEngineRenderer* BagDialog_;
	GameEngineRenderer* DialogBox_;
	GameEngineRenderer* DialogArrow_;

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

	std::vector<class GameEngineContentFont*> ItemNameFonts_; //아이템 이름
	std::vector<class GameEngineContentFont*> ItemDescFonts_; //아이템 내용
	std::vector<class GameEngineContentFont*> ItemOverlapFonts_; //아이템 개수
	std::vector<class GameEngineContentFont*> DialogFonts_; //다이얼로그 창 

	int BagIndex_; //가방 순서

	//가방 움직임
	float BagMoveTime_;
	bool IsMove_;

	//화살표 움직임
	float ArrowMoveTime_;
	bool IsArrowSync_;

	//다이얼로그 상자 인덱스
	int DialogIndex_;

	Item* CurrentItem_;
	Pokemon* CurrentPokemon_;

	GameEngineActor* ChildUI_;

	//입력 대기 시간 
	float InputTime_;
};

