#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <stdio.h>
#include <stdlib.h>
#include "Pokemon.h"

// 설명 : BattleLevel에서 생성되는 인터페이스를 제외한 모든 렌더러를 가지고 있는 Actor
class BattleUnitRenderer : public GameEngineActor
{
public:
	// constrcuter destructer
	BattleUnitRenderer();
	~BattleUnitRenderer();

	// delete Function
	BattleUnitRenderer(const BattleUnitRenderer& _Other) = delete;
	BattleUnitRenderer(BattleUnitRenderer&& _Other) noexcept = delete;
	BattleUnitRenderer& operator=(const BattleUnitRenderer& _Other) = delete;
	BattleUnitRenderer& operator=(BattleUnitRenderer&& _Other) noexcept = delete;


	static GameEngineRenderer* PlayerRenderer_;


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

	//병문씨가 도움주신 변수
	GameEngineRenderer* OpponentRenderer_;

	//김예나 : 5월28일 옮기기용 포인터///////////////////////
	class BattleInterface* BattleInter;

	GameEngineRenderer* MonsterBall;
	float BallLerp;
	//////////////////////////////////////////////////////

	float4 PlayerPokemonPos_;
	float4 OpponentPokemonPos_;
	float4 PlayerRendererPos_;
	float4 OpponentRenderer_Pos_;

	float PlayerTime_;
	float MoveSpeed;

	bool PlayerStop;//김예나 : 일정 위치 도착하면 멈추도록 할 조건문
	bool FirstMove;//김예나 : PlayerStop계속 들어오지 않도록 조건문용 bool
	bool Fighting;//김예나 : 싸움 채팅중엔 꺼져야함

	float TimeCheck;

	float MyMoveTime;//김예나: 내 푸키먼 공격시 타임체크해서 그 시간을 기반으로 움직이게끔
	bool MyTurnEnd;//김예나: 내 푸키먼 공격무빙이 끝나면 MoveTime초기화용

	float Angle;//회전용..?
	float EffectX;//이펙트 실시간x위치
	float EffectY;//이펙트 실시간y위치

	class BattleLevel* Level_;
	class BattleData* BattleDataR_;

	void ShowDebugValue();
public:
	void Opening();
	void Opening2();
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
	void SetFighting(bool Value)
	{
		Fighting = Value;
	}
};

