#pragma once
#include "NPCBase.h"

// Ό³Έν :
class NPC4 : public NPCBase
{
public:
	// constrcuter destructer
	NPC4();
	~NPC4();

	// delete Function
	NPC4(const NPC4& _Other) = delete;
	NPC4(NPC4&& _Other) noexcept = delete;
	NPC4& operator=(const NPC4& _Other) = delete;
	NPC4& operator=(NPC4&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* NPCRender_;

	void Start() override;
	void Update() override;
};

