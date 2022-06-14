#pragma once
#include "NPCBase.h"

// 설명 :
class Oak : public NPCBase
{
public:
	// constrcuter destructer
	Oak();
	~Oak();

	// delete Function
	Oak(const Oak& _Other) = delete;
	Oak(Oak&& _Other) noexcept = delete;
	Oak& operator=(const Oak& _Other) = delete;
	Oak& operator=(Oak&& _Other) noexcept = delete;

	static Oak* MainOak_;

	inline void SetRedOut(bool _bRedOutCheck)
	{
		RedOutCheck_ = _bRedOutCheck;
	}

	inline bool GetRedOut()
	{
		return RedOutCheck_;
	}

	inline void SetStartShop(int _Index, bool _On)
	{
		IsStartShop_[_Index] = _On;
	}

protected:

private:
	void Start() override;
	void Update() override;

	std::vector<bool> IsStart_;
	std::vector<bool> IsStartShop_;
	bool RedOutCheck_;
	int OakCurrentIndexX_;
	int OakCurrentIndexY_;

	void OakMoveIndexPos(int _X, int _Y);

	// 숲으로 들어갈 때 오박사 부름
	void RedCatch();
	// 대화 후 오박사 따라 레드 이동
	void OakFollow();
	// 오박사 따라 레드도 연구실 입장
	void Room4Enter();
	// 포켓몬 미선택 시 상호작용
	//void Room4Idle();
	// 그린과의 대전 이후 상호작용
	//void OakIdle();
	// 상점 이벤트
	void ShopEvent();
	// 상점 이벤트 이후 상호작용
	//void ShopEventIdle();

};

