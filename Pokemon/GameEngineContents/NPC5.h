#pragma once
#include "NPCBase.h"

// Ό³Έν :
class NPC5 : public NPCBase
{
public:
	// constrcuter destructer
	NPC5();
	~NPC5();

	// delete Function
	NPC5(const NPC5& _Other) = delete;
	NPC5(NPC5&& _Other) noexcept = delete;
	NPC5& operator=(const NPC5& _Other) = delete;
	NPC5& operator=(NPC5&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

