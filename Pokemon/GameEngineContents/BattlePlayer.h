#pragma once

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class BattlePlayer
{
public:
	//디폴트 생성자
	BattlePlayer();
	//디폴트 소멸자
	~BattlePlayer();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	BattlePlayer(const BattlePlayer& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	BattlePlayer(BattlePlayer&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	BattlePlayer& operator=(const BattlePlayer& _Other) = delete;
	BattlePlayer& operator=(BattlePlayer&& _Other) noexcept = delete;


protected:

private:

};

