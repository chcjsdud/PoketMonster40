#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentEnum.h"

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
	
protected:
	void Start() override;
	void Update() override;
	
private:
	class GameEngineContentFont* Fonts_;
	WorldBackgroundSoundEnum CurrentRegion_;
	WorldBackgroundSoundEnum NextRegion_;
	float4 StartPos_;
	float4 GoalPos_;
	float LerpTimer_;
	bool IsShow_;
	bool IsHide_;
	bool IsShowing_;

	void Show();
	void Hide();
};

