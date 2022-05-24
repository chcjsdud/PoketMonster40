#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "BattleNPCInterface.h"
#include "PlayerRed.h"
#include "BattleInterface.h"
#include "BattleEnum.h"
#include "Pokemon.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 

enum class PokemonAbility;
class BattleEngine;
class PokemonBattleState;
class BattleLevel : public GameEngineLevel
{
	friend class BattleInterface;
public:
	//디폴트 생성자
	BattleLevel();
	//디폴트 소멸자
	~BattleLevel();
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	BattleLevel(const BattleLevel& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	BattleLevel(BattleLevel&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	BattleLevel& operator=(const BattleLevel& _Other) = delete;
	BattleLevel& operator=(BattleLevel&& _Other) noexcept = delete;

	inline BattleState GetBattleState() const
	{
		return BState_;
	}

	//inline PlayerRed* GetRed() const
	//{
	//	return PlayerRed_;
	//}

public:
	inline void OpenningEnd()
	{
		OpenningEnd_ = true;
	}
	inline void EnddingEnd()
	{
		EnddingEnd_ = true;	
	}

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	BattleInterface* Interface_;
	BattleState BState_;


	// 오프닝 관련
	void ShowOpenning();
	bool OpenningEnd_;
	//
	
	// 엔딩 관련
	void ShowEndding();
	bool EnddingEnd_;
	//
	



	//전투시 폰트 출력
	class GameEngineContentFont* Fonts;
	class BattleUnitRenderer* PlayerStopCheck;

	bool OneTalk;

private:
	// 플레이어 및 NPC
	PlayerRed* PlayerRed_;
	BattleNPCInterface* Opponent_;
	// Pokemon
	Pokemon* PlayerCurrentPokemon_; // Debug
	Pokemon* PoeCurrentPokemon_;// Debug
	//

	
};

class BattleData
{
	friend BattleLevel;
private:
	BattleData(PlayerRed* _Player, BattleNPCInterface* _Poe, BattleLevel* _Level);
	BattleData(PlayerRed* _Player, Pokemon* _WildPokemon, BattleLevel* _Level);
	~BattleData();

	BattleData(const BattleData& _Other) = delete;
	BattleData(BattleData&& _Other) noexcept = delete;
	BattleData& operator=(const BattleData& _Other) = delete;
	BattleData& operator=(BattleData&& _Other) noexcept = delete;

private:
	PlayerRed* Player_;
	BattleNPCInterface* PoeNPC_;

	// Data 출력

	// 주머니속 가지고 있는 포켓몬
	std::vector<Pokemon*>& PlayerPokemonList_;
	std::vector<Pokemon*>& PoePokemonList_;


	// PokemonBatleState
	PokemonBattleState* PlayerCurrentPokemonInBattle_;
	PokemonBattleState* PoeCurrentPokemonInBattle_;


	std::vector<PokemonBattleState*> PlayerPokemonsInBattle_;
	std::vector<PokemonBattleState*> PeoPokemonsInBattle_;

	std::vector<PokemonBattleState*> AllPokemonInBattle_;

	bool WildBattle_;

	PokemonBattleState* CreatePokemonState(Pokemon* _Pokemon);
};

class PokemonBattleState
{
	// 중첩 클래스 전방선언
	class ApplySkill;
	// PokemonBattleState();
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
	// 고정된 포켓몬
	const Pokemon* Pokemon_;

	// 행동 가능여부
	bool CanAction_;

	//현재 랭크 상태
	std::map<PokemonAbility, int> CurrentRank_;

	// PokemonSkill 상속에 virtual 함수 Ing, End 필요
	std::list<PokemonBattleState::ApplySkill*> AllCurrentApplySkill_;

	// 현재 적용받는 스킬들
	class ApplySkill
	{
	private:
		ApplySkill();
	public:
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
	private:
		const PokemonBattleState* CastPokemon_;
		const PokemonSkill* Skill_;
		int LeftTurn_;
	};


};


class BattleManager
{
public:
	BattleManager();
	~BattleManager();

	BattleManager(const BattleManager& _Other) = delete;
	BattleManager(BattleManager&& _Other) noexcept = delete;
	BattleManager& operator=(const BattleManager& _Other) = delete;
	BattleManager& operator=(BattleManager&& _Other) noexcept = delete;


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
