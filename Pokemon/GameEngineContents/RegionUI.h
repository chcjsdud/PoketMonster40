#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentEnum.h"

enum class RegionState
{
	None,
	Show,
	Hide,
	Appear,
	Disappear,
	Max,
};

class RegionUI : public GameEngineActor
{
private:
	static RegionUI* Inst_;

public:
	static RegionUI* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	RegionUI();
	~RegionUI();

	// delete Function
	RegionUI(const RegionUI& _Other) = delete;
	RegionUI(RegionUI&& _Other) noexcept = delete;
	RegionUI& operator=(const RegionUI& _Other) = delete;
	RegionUI& operator=(RegionUI&& _Other) noexcept = delete;

	void ChangeRegion(WorldBackgroundSoundEnum _Enum);
	void NoneNamedRegion();

protected:
	void Start() override;
	void Update() override;
	
private:
	class GameEngineContentFont* Fonts_;
	WorldBackgroundSoundEnum CurrentRegion_;
	WorldBackgroundSoundEnum NextRegion_;
	GameEngineRenderer* Renderer_;
	float4 DisappearPos_;
	float4 AppearPos_;
	float LerpTimer_;

	// FSM
	RegionState CurrentState_;

	void ChangeState(RegionState _State);
	void StateUpdate();

	void ShowStart();
	void HideStart();
	void AppearStart();
	void DisappearStart();

	void ShowUpdate();
	void HideUpdate();
	void AppearUpdate();
	void DisappearUpdate();
};

