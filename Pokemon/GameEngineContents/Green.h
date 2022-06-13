#pragma once
#include "NPCBase.h"

// 설명 :
class Green : public NPCBase
{
public:
	// constrcuter destructer
	Green();
	~Green();

	// delete Function
	Green(const Green& _Other) = delete;
	Green(Green&& _Other) noexcept = delete;
	Green& operator=(const Green& _Other) = delete;
	Green& operator=(Green&& _Other) noexcept = delete;

	static Green* NPCGreen;

	bool IsRedSelectFinish_;
	bool IsGreenMove_;

	inline void SetGreenMove(const bool _Value)
	{
		IsGreenMove_ = _Value;
	}

	inline bool GetGreenMove()
	{
		return IsGreenMove_;
	}

protected:

private:
	void Start() override;
	void Update() override;

	std::vector<bool> IsStart_;

	// 레드 포켓몬 선택 이후 그린 포켓몬 선택 및 대화
	void RedSelectPokemonAfter();

	// 레드와 그린 배틀 시작을 위한 움직임
	void RedGreenBattle();
};

