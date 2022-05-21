#pragma once
#include <GameEngine/GameEngineActor.h>
#include "PokemonSkill.h"
#include "ContentEnum.h"
#include "Pokemon.h"
#include "PokemonInfoManager.h"
#include "ContentEnum.h"
#include <GameEngineBase/GameEngineRandom.h>

// 설명 :
class BattleLevel;
class BattlePageSupport;
class PokemonBattleState;
enum class TypeDamge;
enum class BattleTurn;
class BattleEngine : public GameEngineActor
{
public:
	// constrcuter destructer
	BattleEngine();
	~BattleEngine();

	// delete Function
	BattleEngine(const BattleEngine& _Other) = delete;
	BattleEngine(BattleEngine&& _Other) noexcept = delete;
	BattleEngine& operator=(const BattleEngine& _Other) = delete;
	BattleEngine& operator=(BattleEngine&& _Other) noexcept = delete;


	BattleTurn CurrentTurn_;

	void ScanBattleLevel();
	void BattlePage(const std::string& _PlayerSkill, const std::string& _OpponentSkill);

protected:
	void Update() override;
	void Start() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	BattleLevel* BattleLevel_;
	GameEngineRandom* Random_;
	
	Pokemon* PlayerPokemon_;
	Pokemon* OpponentPokemon_;
	void InitialReSetting();


// Battle관련
private:
	BattlePageSupport* BattleFirstSupporter_;
	BattlePageSupport* BattleSecondSupporter_;
	
	bool BattleStart_;
	bool PlayerTurn_;
};
class PokemonBattleState
{
public:
	
};

class BattlePageSupport
{
public:
	BattlePageSupport(Pokemon* _AttackPokemon, Pokemon* _DefensePokemon, PokemonSkill* _Skill);
	~BattlePageSupport();


	BattlePageSupport(const BattlePageSupport& _Other) = delete;
	BattlePageSupport(BattlePageSupport&& _Other) noexcept = delete;
	BattlePageSupport& operator=(const BattlePageSupport& _Other) = delete;
	BattlePageSupport& operator=(BattlePageSupport&& _Other) noexcept = delete;
	TypeDamge DamgeType_;
	int GetFinalValue()
	{
		return FinalValue_;
	}


	void UseSkillTurn();

private:
	Pokemon* AttackPokemon_;
	Pokemon* DefensePokemon_;
	PokemonSkill* AttackPokemonSkill_;

	int FinalValue_;
	GameEngineRandom* Random_;
	TypeDamge ComparePokemonType(const PokemonType& _Attack, const PokemonType& _Defend);

private:
	BattlePageSupport() {}
};

enum class BattleTurn
{
	Off,
	Wait,
	FirstTurn,
	SecondTurn,
	End
};

enum class TypeDamge
{
	Error,
	Great,
	Nomal,
	Bad,
	Nothing
};

enum class PokemonState
{
	Att,
	Def, 
	Speed,
	
};
