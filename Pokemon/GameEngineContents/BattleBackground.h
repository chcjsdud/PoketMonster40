#pragma once
#include <GameEngine/GameEngineActor.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class BattleBackground : public GameEngineActor
{
public:
	//디폴트 생성자
	BattleBackground();
	//디폴트 소멸자
	~BattleBackground();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	BattleBackground(const BattleBackground& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	BattleBackground(BattleBackground&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	BattleBackground& operator=(const BattleBackground& _Other) = delete;
	BattleBackground& operator=(BattleBackground&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* BackgroundRender;
	GameEngineRenderer* TextRender;
	GameEngineRenderer* BattleSelect;

private:
	void Start() override;
		// 지속적으로 게임이 실행될때 호출된다.
	void Update() override;
		// 지속적으로 게임이 실행될때 호출된다.
	void Render() override;

};

