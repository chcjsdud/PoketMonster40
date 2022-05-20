#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "PlayerRed.h"
#include "BattleInerface.h"
#include "BattleEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class BattleEngine;
class BattleLevel : public GameEngineLevel
{
	friend BattleEngine;
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

	inline PlayerRed* GetRed()
	{
		return PlayerRed_;
	}
	

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
	BattleInerface* Interface;
	BattleState BState_;

	// 오프닝 관련
	void ShowOpenning();
	bool OpenningEnd_;

	// 엔딩 관련
	void ShowEndding();
	bool EnddingEnd_;

	BattleEngine* BEngine_;
	// 플레이어
	PlayerRed* PlayerRed_;

	//전투시 폰트 출력
	class GameEngineContentFont* Fonts;
	class BattleUnitRenderer* PlayerStopCheck;

	bool OneTalk;
};