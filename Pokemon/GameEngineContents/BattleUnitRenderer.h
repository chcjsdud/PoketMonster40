#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include "BattleEnum.h"
#include <stdio.h>
#include <stdlib.h>
#include "Pokemon.h"

// 설명 : BattleLevel에서 생성되는 인터페이스를 제외한 모든 렌더러를 가지고 있는 Actor
class BattleLevel;
class BattleUnitRenderer : public GameEngineActor
{
	friend class BattleManager;
public:
	// constrcuter destructer
	BattleUnitRenderer();
	~BattleUnitRenderer();

	// delete Function
	BattleUnitRenderer(const BattleUnitRenderer& _Other) = delete;
	BattleUnitRenderer(BattleUnitRenderer&& _Other) noexcept = delete;
	BattleUnitRenderer& operator=(const BattleUnitRenderer& _Other) = delete;
	BattleUnitRenderer& operator=(BattleUnitRenderer&& _Other) noexcept = delete;


	inline bool GetMyAniTurn() const
	{
		return MyTurnEnd;
	}
	inline bool GetPoeAniTurn() const
	{
		return EnemyTurnEnd;
	}

	

	static GameEngineRenderer* PlayerRenderer_;

	SkillName SkillName_;


protected:
	void Start() override;
	void Update() override;
	void Render() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	


private:
	GameEngineRenderer* PlayerCurrentPokemon_;
	GameEngineRenderer* PoeCurrentPokemon_;
	GameEngineRenderer* MyTackleEffect;//김예나 : 6월 3일 몸통박치기 이팩트 렌더러 추가
	GameEngineRenderer* MyWaterGunEffect;
	GameEngineRenderer* EnemyTackleEffect;
	GameEngineRenderer* Rock1;
	GameEngineRenderer* Rock2;
	GameEngineRenderer* Rock3;
	GameEngineRenderer* Rock4;
	GameEngineRenderer* X;
	GameEngineRenderer* CatchBallOpen;
	GameEngineRenderer* MonsterBallOP;
	GameEngineRenderer* MonsterBallCH;
	GameEngineRenderer* MyGrowl1;
	GameEngineRenderer* MyGrowl2;
	GameEngineRenderer* MyGrowl3;
	GameEngineRenderer* EnemyGrowl1;
	GameEngineRenderer* EnemyGrowl2;
	GameEngineRenderer* EnemyGrowl3;

	//병문씨가 도움주신 변수
	GameEngineRenderer* OpponentRenderer_;

	//김예나 : 5월28일 옮기기용 포인터///////////////////////
	class BattleInterface* BattleInter;

	float BallLerp;
	//////////////////////////////////////////////////////

	float BallX;
	float BallY;
	float CatchBallTime;
	float4 CatchBallPivot;
	float Alpha_Time;
	float BallFall;
	float BallFallTime;

	float4 PlayerPokemonPos_;
	float4 OpponentPokemonPos_;
	float4 PlayerRendererPos_;
	float4 OpponentRenderer_Pos_;

	float PlayerTime_;
	float PlayerTime_2;
	float MoveSpeed;
	float RockSpeed;

	bool PlayerStop;//김예나 : 일정 위치 도착하면 멈추도록 할 조건문
	bool FirstMove;//김예나 : PlayerStop계속 들어오지 않도록 조건문용 bool
	bool Fighting;//김예나 : 싸움 채팅중엔 꺼져야함
	bool FallCheck;//몬스터볼 던진후 바닥에 닿았는지
	bool IsCatch;//잡힌애인지 안잡힌 애인지(푸키먼 잡힌 상태에 따른 On, Off용)

	float TimeCheck;

	float MyMoveTime;//김예나: 내 푸키먼 공격시 타임체크해서 그 시간을 기반으로 움직이게끔
	bool MyTurnEnd;//김예나: 내 푸키먼 공격무빙이 끝나면 MoveTime초기화용
	bool MyCatchEnd;
	bool EnemyTurnEnd;

	float Angle;//회전용..?
	float EffectX;//이펙트 실시간x위치
	float EffectY;//이펙트 실시간y위치
	
	float4 Rock1Pivot;
	bool Rock1End;
	float4 Rock2Pivot;
	bool Rock2End;
	float4 Rock3Pivot;
	bool Rock3End;
	float4 Rock4Pivot;
	bool Rock4End;
	
	float AnimationEndTime;

	BattleLevel* Level_;
	class BattleData* BattleDataR_;

	void ShowDebugValue();
	bool Debug_;
public:
	void Opening();
	void Opening2();
	void TrainerOpening1();
	void TrainerOpening2();
	void DoomChit();
	bool GetPlayerStop() const
	{
		return PlayerStop;
	}
	void SetPlayerStop(bool Value)
	{
		PlayerStop = Value;
	}
	//김예나 전투 무빙 추가중(6월 2일)
	void Tackle();
	void WaterGun();
	void TailWhipMove();
	void ShellHide();
	void MyGrowl();
	void EnemyGrowl();
	void SetFighting(bool Value)
	{
		Fighting = Value;
	}
	
	void EnemyRock();
	void EnemyTackle();
	void Catch();
	void NextPokemonAppear();
	GameEngineRenderer* GetPoeCurrentPokemonRender()
	{
		return PoeCurrentPokemon_;
	}
};

