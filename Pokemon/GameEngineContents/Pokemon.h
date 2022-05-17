#pragma once
#include <string>
#include "ContentEnum.h"
#include <GameEngine/GameEngineActor.h>

class Pokemon : public GameEngineActor
{
public:
	Pokemon();
	~Pokemon();

	Pokemon(const Pokemon& _Other) = delete;
	Pokemon(Pokemon&& _Other) noexcept = delete;
	Pokemon& operator=(const Pokemon& _Other) = delete;
	Pokemon& operator=(Pokemon&& _Other) noexcept = delete;

protected:

private:
	std::string Name_;
	PokemonType Type_;
	StatusEffect Effect_; //상태이상

	int Lv_;
	int MaxLv_;
	int Exp_;
	int MaxExp_;
	int Att_;
	int Def_;
	int SpAtt_;
	int SpDef_;
	int Speed_;

	bool IsPlayer_;

	GameEngineRenderer* BattleBack_; //전투 뒷모습(플레이어 포켓몬
	GameEngineRenderer* BattleFront_; //전투 앞모습(적 혹은 야생 포켓몬
	GameEngineRenderer* MyProfile_; //도감 혹은 상세메뉴 이미지
	GameEngineRenderer* MyIcon_; //지닌 포켓몬 아이콘

};

