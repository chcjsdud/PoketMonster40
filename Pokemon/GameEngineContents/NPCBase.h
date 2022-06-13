#pragma once
#include <GameEngine/GameEngineActor.h>
#include "PokemonTileMap.h"

enum class NPCState
{
	Idle,
	Walk,

	Max
};
enum class NPCDir
{
	Up,
	Down,
	Left,
	Right,

};
// Ό³Έν :
class GameEngineCollision;
class NPCBase : public GameEngineActor
{
public:
	// constrcuter destructer
	NPCBase();
	~NPCBase();

	// delete Function
	NPCBase(const NPCBase& _Other) = delete;
	NPCBase(NPCBase&& _Other) noexcept = delete;
	NPCBase& operator=(const NPCBase& _Other) = delete;
	NPCBase& operator=(NPCBase&& _Other) noexcept = delete;

	static NPCBase* NPC_;
	static bool IsTalk_;

	GameEngineRenderer* NPCRender_;
	
	void Start() override;
	void Update() override;
	void Render() override;

	inline void SetNPCInteraction(const bool _Value)
	{
		IsTalk_ = _Value;
	}

	inline void SetOakFollow(bool _Value)
	{
		OakFollowCheck_ = _Value;
	}

	inline void SetRoon4Enter(bool _Value)
	{
		Room4EnterCheck_ = _Value;
	}

	inline bool GetRedCathEnd()
	{
		return RedCatchEndCheck_;
	}

	inline bool GetOakFollow()
	{
		return OakFollowCheck_;
	}

	inline bool GetRoom4Enter()
	{
		return Room4EnterCheck_;
	}

protected:
	void NPCMove();
	void NPCMoveDir(NPCDir _Dir, int _Count);
	void NPCMoveAnim();
	void NPCInteractDir();
	bool IsInside(float4 _LeftTop, float4 _RightBot);
	PokemonTileMap*			CurrentTileMap_;
	//GameEngineRenderer*		NPCRender_;
	GameEngineCollision*	NPCCollision_;
	GameEngineCollision*	NPCUpCollision_;
	GameEngineCollision*	NPCDownCollision_;
	GameEngineCollision*	NPCRightCollision_;
	GameEngineCollision*	NPCLeftCollision_;
	std::string				NPCAnimationName_;
	std::string				NPCChangeDirText_;

	float4 InSideLeftTop_;
	float4 InSideRightBot_;
	float NPCLerpX_;
	float NPCLerpY_;
	float NPCLerpTime_;
	float NPCNextMoveTime_;
	float NextDirMoveTimer_;
	bool  IsMove_;
	bool RedCatchEndCheck_;
	bool OakFollowCheck_;
	bool Room4EnterCheck_;
	int Count_;

private:
	float4	StartPos_;
	float4	GoalPos_;
	float4	NPCMoveDir_;

	NPCState State_;
	NPCDir CurrentDir_;
};

