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
	// 두줄씩 출력하는 것을 권장
	// 
	// True  : 출력 예약 성공적으로 완료
	// False : 이미 등록된 출력 명령이 있음
	//
	// _String : 출력할 문장	
	// _ShowAllText : 애니메이션 형태로 출력 하려면 false, 한번에 출력하려면 true
	// _LineHeight : 줄 간 간격
	// _DelayTime : 문자 간 출력 딜레이
	// _Order : Renderer Order
	bool ShowString(const std::string& _String, bool _ShowAllText = false, float _LineHeight = 60.0f, float _DelayTime = 0.02f);


	// 텍스트 출력 애니메이션을 생략시키고 싶을때 이용하는 함수
	// 
	// 호출 시 대기 텍스트 들이 모두 호출된다 (단, 두 줄 이하)
	inline void SkipCharAnimation()
	{
		ShowAllText_ = true;
	}

	// 출력 완료 후 키 입력 대기 중인지 확인하는 함수
	//
	// True  : 입력 대기 중
	// False : 출력 중이거나 입력 대기중이 아님
	inline bool IsWait() const
	{
		return (WatingKeyPush_ && !StringQueue_.empty());
	}

	// 모든 문장이 출력이 되었는지 확인하는 함수
	//
	// True	 : 모든 문장 출력 완료
	// False : 아직 대기열에 있는 문장이 있음
	inline bool IsEnd() const
	{
		return (StringQueue_.empty() && WatingKeyPush_);
	}

	// 화면에 출력된 폰트 삭제 후 다음 문장 재생
	// 
	// True  : 현재 화면에 그려진 문장을 지우고 다음 문장 재생
	// False : 다음 문장이 없거나 이미 재생중
	bool NextString()
	{
		if (!StringQueue_.empty() && WatingKeyPush_ == true)
		{
			ClearCurrentFonts();
			WatingKeyPush_ = false;
			return true;
		}
		else
		{
			return false;
		}
	}

	// 화면 내 출력된 폰트 제거
	// 
	// 
	// NextString과 ClearFonts 차이점
	// 
	// 바로 다음 문장을 재생하고 싶다 
	// -> NextString(화면에 출력된 폰트를 지우고 다음 문장 재생)
	// 
	// 어떤 모션이나 액션, 애니메이션을 재생하고 끝난뒤에 문장을 출력하고싶다
	//
	// -> ClearFonts(화면상 출력된 폰트를 지운다) 
	// -> 액션 혹은 애니메이션 출력 
	// -> NextString(화면에 출력된 폰트 지우고 다음 문장 재생인데, 화면상 출력된 폰트는 이미 지웠으니 그냥 다음 문장 재생)
	//
	void ClearCurrentFonts()
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
	}

	// 출력 중이거나 대기중인 모든 문장들을 삭제
	// 묻지도, 따지지도 않고 모든 문장을 제거합니다
	void EndFont()
	{
		for (auto Iter : AllFontRenderer_)
		{
			if (Iter != nullptr)
			{
				Iter->Death();
				Iter = nullptr;
			}
		}
		StringQueue_ = std::queue<std::string>();
		CurrentString_.clear();
		ShowAllText_ = false;
		WatingKeyPush_ = false;
		Off();
	}


	// 폰트가 출력되어있는지 확인하는 함수
	// true : 있음
	// false : 없음
	inline bool IsRendererFont()
	{
		if (AllFontRenderer_.empty())
		{
			return false;
		}
		else
		{
			return true;
		}

	}


	const std::string& GetCurrentString() 
	{
		return CurrentString_;
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

	// 줄 높이
	float LineHeight_;
	
	// 키 푸시 대기
	bool WatingKeyPush_;

	// 한번에 출력
	bool ShowAllText_;


	std::queue<std::string> StringQueue_;

	std::string CurrentString_;
	std::vector<GameEngineRenderer*> AllFontRenderer_;
	// static std::list<GameEngineContentFont*> AllFonts_;
};