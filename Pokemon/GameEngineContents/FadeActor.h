#pragma once
#include <GameEngine/GameEngineActor.h>

class FadeActor : public GameEngineActor
{
public:
	FadeActor();
	~FadeActor();

	FadeActor(const FadeActor& _Other) = delete;
	FadeActor(FadeActor&& _Other) noexcept = delete;
	FadeActor& operator=(const FadeActor& _Other) = delete;
	FadeActor& operator=(FadeActor&& _Other) noexcept = delete;

	void FadeIn();
	void FadeOut();

	inline bool GetChange()
	{
		return IsChange_;
	}

protected:
	void Start() override;
	void Update() override;

private:
	class GameEngineRenderer* Background_;

	float Alpha_;

	bool FadeIn_;
	bool Fadeout_;

	bool IsChange_;
};

