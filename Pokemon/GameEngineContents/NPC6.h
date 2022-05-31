#pragma once
#include "NPCBase.h"

// Ό³Έν :
class NPC6 : public NPCBase
{
public:
	// constrcuter destructer
	NPC6();
	~NPC6();

	// delete Function
	NPC6(const NPC6& _Other) = delete;
	NPC6(NPC6&& _Other) noexcept = delete;
	NPC6& operator=(const NPC6& _Other) = delete;
	NPC6& operator=(NPC6&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

};

