#pragma once
#include <string>
#include <vector>
#include "ContentEnum.h"
#include <GameEngine/GameEngineActor.h>

class PokemonSkill;
class Pokemon : public GameEngineActor
{
public:
	Pokemon();
	~Pokemon();

	Pokemon(const Pokemon& _Other) = delete;
	Pokemon(Pokemon&& _Other) noexcept = delete;
	Pokemon& operator=(const Pokemon& _Other) = delete;
	Pokemon& operator=(Pokemon&& _Other) noexcept = delete;


	//타입 및 상태 관련 함수
	inline void SetMyType(PokemonType _Type)
	{
		Type_ = _Type;
	}

	inline PokemonType GetMyType()
	{
		return Type_;
	}

	inline void SetStatusEffect(StatusEffect _Status)
	{
		Effect_ = _Status;
	}

	inline StatusEffect SetStatusEffect()
	{
		return Effect_;
	}



	//능력치 관련 함수
	inline int GetMyLevel()
	{
		return Lv_;
	}

	inline void SetMyLevel(int _Lv)
	{
		Lv_ = _Lv;
	}

	inline int GetMyMaxLevel(int _MaxLv)
	{
		return MaxLv_;
	}

	inline void SetMyMaxLevel(int _MaxLv)
	{
		MaxLv_ = _MaxLv;
	}

	inline int GetHp()
	{
		return Hp_;
	}

	inline void SetHp(int _Hp)
	{
		Hp_ = _Hp;
	}

	inline int GetMaxHp()
	{
		return MaxHp_;
	}

	inline void SetMaxHp(int _MaxHp)
	{
		MaxHp_ = _MaxHp;
	}

	inline int GetExp()
	{
		return Exp_;
	}

	inline void SetExp(int _Exp)
	{
		Exp_ = _Exp;
	}

	inline int GetMaxExp()
	{
		return MaxExp_;
	}

	inline void SetMaxExp(int _MaxExp)
	{
		MaxExp_ = _MaxExp;
	}

	inline int GetAtt()
	{
		return Att_;
	}

	inline void SetAtt(int _Att)
	{
		Att_ = _Att;
	}

	inline int GetSpAtt()
	{
		return SpAtt_;
	}

	inline void SetSpAtt(int _SpAtt)
	{
		SpAtt_ = _SpAtt;
	}

	inline int GetDef()
	{
		return Def_;
	}

	inline void SetDef(int _Def)
	{
		Def_ = _Def;
	}

	inline int GetSpDef()
	{
		return SpDef_;
	}

	inline void SetSpDef(int _SpDef)
	{
		SpDef_ = _SpDef;
	}

	inline int GetSpeed()
	{
		return Speed_;
	}

	inline void SetSpeed(int _Speed)
	{
		Speed_ = _Speed;
	}



	//플레이어의 포켓몬인지 체크
	inline bool GetIsPlayer()
	{
		return IsPlayer_;
	}

	inline void SetIsPlayer(bool _IsPlayer)
	{
		IsPlayer_ = _IsPlayer;
	}

	inline bool GetGender()
	{
		return IsGender_;
	}

	inline void SetIsGender(bool _IsGender)
	{
		IsGender_ = _IsGender;
	}



	//렌더러 관련 함수
	inline GameEngineRenderer* GetMyBattleBack()
	{
		return BattleBack_;
	}

	inline void SetMyBattleBack(GameEngineRenderer* _Image)
	{
		BattleBack_ = _Image;
	}

	inline GameEngineRenderer* GetMyBattleFront()
	{
		return BattleFront_;
	}

	inline void SetMyBattleFront(GameEngineRenderer* _Image)
	{
		BattleFront_ = _Image;
	}

	inline GameEngineRenderer* GetMyMyProfile()
	{
		return MyProfile_;
	}

	inline void SetMyMyProfile(GameEngineRenderer* _Image)
	{
		MyProfile_ = _Image;
	}

	inline GameEngineRenderer* GetMyIcon()
	{
		return MyIcon_;
	}

	inline void SetMyIcon(GameEngineRenderer* _Image)
	{
		MyIcon_ = _Image;
	}

protected:
	void Start() override;
	void Update() override;

private:
	PokemonType Type_;
	StatusEffect Effect_; //상태이상

	int Lv_;
	int MaxLv_;
	int Hp_;
	int MaxHp_;
	int Exp_;
	int MaxExp_;
	int Att_;
	int Def_;
	int SpAtt_;
	int SpDef_;
	int Speed_;

	bool IsPlayer_; //플레이어 포켓몬인지 아닌지
	bool IsGender_; //true: 수컷, false: 암컷

	GameEngineRenderer* BattleBack_; //전투 뒷모습(플레이어 포켓몬
	GameEngineRenderer* BattleFront_; //전투 앞모습(적 혹은 야생 포켓몬
	GameEngineRenderer* MyProfile_; //도감 혹은 상세메뉴 이미지
	GameEngineRenderer* MyIcon_; //지닌 포켓몬 아이콘

	std::vector<PokemonSkill*> MySkills_;
};

