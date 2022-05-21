#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 전투 선택지를 띄우는 인터페이스

enum class BattleOrder
{
	Fight,
	Pokemon,
	Bag,
	Run,
	None
};

class GameEngineImage;
class BattleInterface : public GameEngineActor
{
public:
	//디폴트 생성자
	BattleInterface();
	//디폴트 소멸자
	~BattleInterface();
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	BattleInterface(const BattleInterface& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	BattleInterface(BattleInterface&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	BattleInterface& operator=(const BattleInterface& _Other) = delete;
	BattleInterface& operator=(BattleInterface&& _Other) noexcept = delete;



	GameEngineRenderer* GetSelect()
	{
		return Select;
	}
	GameEngineRenderer* GetEnemyHPUI()
	{
		return EnemyHPUI;
	}
	GameEngineRenderer* GetMyHPUI()
	{
		return MyHPUI;
	}

protected:
	void Start() override;
	void Render() override;
	void Update() override;

private:
	GameEngineRenderer* InterfaceImage;
	GameEngineRenderer* Select;
	GameEngineRenderer* MyHPUI;
	GameEngineRenderer* EnemyHPUI;
	GameEngineRenderer* MyHP;
	GameEngineRenderer* EnemyHP;
	GameEngineRenderer* EXP;
	GameEngineRenderer* BattleCommend;
	

	BattleInterface* MainInterface;

	BattleOrder CurOrder;

	float TimeCheck;


	void DoomChit();
	void OrderCheck();
	void SelectOrder();
	class BattleLevel* Level_;

public:
	bool MoveKey();
	void FirstBattlePage();
};

