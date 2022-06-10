#pragma once
#include "NPCBase.h"

// Ό³Έν :
class NPCBrock : public NPCBase
{
public:
	// constrcuter destructer
	NPCBrock();
	~NPCBrock();

	// delete Function
	NPCBrock(const NPCBrock& _Other) = delete;
	NPCBrock(NPCBrock&& _Other) noexcept = delete;
	NPCBrock& operator=(const NPCBrock& _Other) = delete;
	NPCBrock& operator=(NPCBrock&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

};

