#pragma once
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "PokemonSkill.h"
#include "ContentEnum.h"
#include "Pokemon.h"
#include "PokemonInfoManager.h"
#include "ContentEnum.h"
#include "BattleNPCInterface.h"

// 설명 :
class BattlePageSupport;
class PokemonBattleState;
enum class TypeDamge;
enum class PokemonAbility;

class BattleEngine
{
private:
	static BattleEngine* Inst_;

	BattleEngine();
	~BattleEngine();

	// delete Function
	BattleEngine(const BattleEngine& _Other) = delete;
	BattleEngine(BattleEngine&& _Other) noexcept = delete;
	BattleEngine& operator=(const BattleEngine& _Other) = delete;
	BattleEngine& operator=(BattleEngine&& _Other) noexcept = delete;
public:
	static inline BattleEngine* GetInst()
	{
		return Inst_;
	}

	static inline void Destroy()
	{
		if (Inst_ != nullptr)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
		
	}

	void ScanBattleLevel();
	void StartBattlePage(const std::string& _PlayerSkill, const std::string& _OpponentSkill);

	void BattleStart(Pokemon* _PlayPokemon, Pokemon* _OpponentPokemon);
	void BattleEnd();

protected:

private:
	GameEngineRandom* Random_;


private:
	PokemonBattleState* CreatePokemon(Pokemon* _Pokemon);
	
	Pokemon* PlayerPokemon_;
	Pokemon* OpponentPokemon_;

	PokemonBattleState* PlayerPokemonState_;
	PokemonBattleState* OpponentPokemonState_;
	void InitialReSetting();

	std::list<PokemonBattleState*> AllPokemonState_;

// Battle관련
private:
	BattlePageSupport* BattleFirstSupporter_;
	BattlePageSupport* BattleSecondSupporter_;
	
	bool BattleStart_;
	bool PlayerTurn_;
};


class PokemonBattleState
{
	// 중첩 클래스 전방선언
	class ApplySkill;
	PokemonBattleState();
public:
	PokemonBattleState(Pokemon* _Pokemon);
	~PokemonBattleState();

	int SetRank(const PokemonAbility& _State, int _Value)
	{
		CurrentRank_[_State] += _Value;
		if (CurrentRank_[_State] > 6)
		{
			return CurrentRank_[_State] = 6;
		}
		else if (CurrentRank_[_State] < (-6))
		{
			return CurrentRank_[_State] = -6;
		}
		else
		{
			return CurrentRank_[_State];
		}
	}

	float GetRank(const PokemonAbility& _State);


	// 몇 턴 동안 지속인지 확인하는 함수 필요
	bool SetSkill(PokemonBattleState* _AlppyPokemon, PokemonSkill* _Skill);
	void Update();

private:
	const Pokemon* Pokemon_;
	bool CanAction_;
	std::map<PokemonAbility, int> CurrentRank_;
	// PokemonSkill 상속에 virtual 함수 Ing, End 필요
	std::list<PokemonBattleState::ApplySkill*> AllCurrentApplySkill_;

	// 현재 적용받는 스킬들
	class ApplySkill
	{
	private:
		ApplySkill();
	public :
		ApplySkill(PokemonBattleState* _CastPokemon, PokemonSkill* _Skill)
			: CastPokemon_(_CastPokemon)
			, Skill_(_Skill)
			, LeftTurn_(0)
		{
			// 턴수 필요
			LeftTurn_ = 1; // 임의의 값
		}
		~ApplySkill() {}

		inline void TurnPass()
		{
			LeftTurn_ -= 1;
		}

		inline int GetLeftTurn() const
		{
			return LeftTurn_;
		}

		void Update() const
		{
			//Skill_->;
		}
	private :
		const PokemonBattleState* CastPokemon_;
		const PokemonSkill* Skill_;
		int LeftTurn_;
	};


};

class BattlePageSupport
{
public:
	BattlePageSupport(PokemonBattleState* _AttackPokemon, PokemonBattleState* _DefensePokemon, PokemonSkill* _Skill);
	~BattlePageSupport();


	BattlePageSupport(const BattlePageSupport& _Other) = delete;
	BattlePageSupport(BattlePageSupport&& _Other) noexcept = delete;
	BattlePageSupport& operator=(const BattlePageSupport& _Other) = delete;
	BattlePageSupport& operator=(BattlePageSupport&& _Other) noexcept = delete;
	int GetFinalValue()
	{
		return FinalValue_;
	}
	TypeDamge DamgeType_;

	void UseSkillTurn();

private:
	PokemonBattleState* AttackPokemon_;
	PokemonBattleState* DefensePokemon_;
	PokemonSkill* AttackPokemonSkill_;

	int FinalValue_;
	GameEngineRandom* Random_;
	TypeDamge ComparePokemonType(const PokemonType& _Attack, const PokemonType& _Defend);

private:
};

enum class TypeDamge
{
	Error,
	Great,
	Nomal,
	Bad,
	Nothing
};

enum class PokemonAbility
{
	Att,
	Def,
	SpAtt,
	SpDef,
	Speed,
	Accuracy,
	Evasion
};
