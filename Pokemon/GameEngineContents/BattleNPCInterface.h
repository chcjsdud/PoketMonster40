#pragma once
#include <GameEngine/GameEngineActor.h>


// 설명 : NPC들이 상속받는 Battle용 Interface
class PlayerRed;
class Pokemon;
class BattleNPCInterface
{
	friend PlayerRed;
public:
	// constrcuter destructer
	BattleNPCInterface();
	virtual ~BattleNPCInterface();

	// delete Function
	BattleNPCInterface(const BattleNPCInterface& _Other) = delete;
	BattleNPCInterface(BattleNPCInterface&& _Other) noexcept = delete;
	BattleNPCInterface& operator=(const BattleNPCInterface& _Other) = delete;
	BattleNPCInterface& operator=(BattleNPCInterface&& _Other) noexcept = delete;

	inline bool IsBattleNPC() const
	{
		return BattleNPC_;
	}

	//
	// 디버그
	inline void PushPokemon(Pokemon* _Pokemon)
	{
		CurrentPossessionPokemons_.push_back(_Pokemon);
	}
	inline std::vector<Pokemon*>& GetPokemonList()
	{
		return CurrentPossessionPokemons_;
	}
	//
	//

	virtual GameEngineActor* GetActor()
	{
		return nullptr;
	}

protected:

	inline void SetBattleNPC(bool _Idx)
	{
		BattleNPC_ = _Idx;
	}

	//Pokemon* CurrentPossessionPokemon_;

	// 현재 가지고 있는 포켓몬
	std::vector<Pokemon*> CurrentPossessionPokemons_;
private:

	// 배틀 할 수 있는 NPC인가?
	bool BattleNPC_;
};

