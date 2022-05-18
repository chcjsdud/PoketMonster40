#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 전투 선택지를 띄우는 인터페이스
class GameEngineImage;
class BattleInerface : public GameEngineActor
{
public:
	//디폴트 생성자
	BattleInerface();
	//디폴트 소멸자
	~BattleInerface();
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	BattleInerface(const BattleInerface& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	BattleInerface(BattleInerface&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	BattleInerface& operator=(const BattleInerface& _Other) = delete;
	BattleInerface& operator=(BattleInerface&& _Other) noexcept = delete;


	GameEngineRenderer* Select;


protected:
	GameEngineRenderer* InterfaceImage;

private:

	BattleInerface* MainInterface;

public:
	void Start() override;
	void Render() override;
	void Update() override;

};

