#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineContentsCore/GameEngineContentFont.h>

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

enum class FightString;
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
	
	GameEngineRenderer* MonsterBall;
	
	BattleInterface* MainInterface;
	

	BattleOrder CurOrder;

	float TimeCheck;


	void DoomChit();
	void OrderCheck();
	void SelectOrder();

	bool PlayerEnd;

	// 생성한 Level
	class BattleLevel* Level_;

	// Font
	GameEngineContentFont* DownFont_;

	//전투시 폰트 출력
	class GameEngineContentFont* Fonts;
	class BattleUnitRenderer* PlayerStopCheck;
	bool OneTalk;

public:
	bool MoveKey();

	// 장중혁 : test
	bool BattleKey();
	void ShowUsedSkillString(const std::string& _AttPokemon, const std::string& _AttSkill);
	void ShowPoeFaintString(const std::string& _PoePokemon);
	void ShowSupperEffectString();
	void ShowCriticalHitString();
	void ShowNotEffective();

	inline bool IsEndString()
	{
		return DownFont_->IsEnd();
	}

};

// 장중혁 : Test
enum class FightString
{
	Used,
	Effective,
	Critical,
	Became
};