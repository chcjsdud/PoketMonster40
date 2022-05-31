#pragma once
#include "NPCBase.h"

// Ό³Έν :
class NPC7 : public NPCBase
{
public:
	// constrcuter destructer
	NPC7();
	~NPC7();

	// delete Function
	NPC7(const NPC7& _Other) = delete;
	NPC7(NPC7&& _Other) noexcept = delete;
	NPC7& operator=(const NPC7& _Other) = delete;
	NPC7& operator=(NPC7&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

};

