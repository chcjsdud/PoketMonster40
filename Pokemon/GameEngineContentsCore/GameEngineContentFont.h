#pragma once
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <list>
#include <string>
#include <queue>

// 설명 :
class GameEngineContentFont : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEngineContentFont();
	~GameEngineContentFont();

	// delete Function
	GameEngineContentFont(const GameEngineContentFont& _Other) = delete;
	GameEngineContentFont(GameEngineContentFont&& _Other) noexcept = delete;
	GameEngineContentFont& operator=(const GameEngineContentFont& _Other) = delete;
	GameEngineContentFont& operator=(GameEngineContentFont&& _Other) noexcept = delete;

	// 텍스트 출력 명령 함수
	//
	// True  : 출력 예약 성공적으로 완료
	// False : 이미 등록된 출력 명령이 있음
	//
	// _String : 출력할 문장
	// _LineHeight : 줄 간 간격
	// _DelayTime : 문자 간 출력 딜레이
	// _Order : Renderer Order
	bool ShowString(const std::string& _String, float _LineHeight = 60.0f, float _DelayTime = 0.02f, int _Order = 10);


	// 출력 완료 후 키 입력 대기 중인지 확인하는 함수
	//
	// True  : 입력 대기 중
	// False : 출력 중이거나 입력 대기중이 아님
	inline bool IsWattingKeyPush() const
	{
		return WatingKeyPush_;
	}


	// 화면 내 해당 인터페이스가 가지고있는 폰트 제거
	inline void ClearFonts()
	{
		for (auto Iter : AllFontRenderer_)
		{
			if (Iter != nullptr)
			{
				Iter->Death();
				Iter = nullptr;
			}
		}
		AllFontRenderer_.clear();
		WatingKeyPush_ = false;
	}

protected:
	void Update() override;
	void Start() override;
	void Render() override {}

private:
	float4 CurrentPivot_;
	float OriginalWaitTime_;
	float CurrentWaitTime_;

	// 현재 줄
	int CurrentStringRow_;
	float LineHeight_;
	//
	// Order
	int Order_;

	// 키 푸시 대기
	bool WatingKeyPush_;
	//


	std::queue<std::string> StringQueue_;

	std::string CurrentString_;
	std::string CurrentWord_;
	std::vector<GameEngineRenderer*> AllFontRenderer_;
	// static std::list<GameEngineContentFont*> AllFonts_;
};