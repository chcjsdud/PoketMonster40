#pragma once

// Ό³Έν :
class BattleEngine
{
private:
	static BattleEngine* Inst_;

	BattleEngine();
	~BattleEngine();

	// delete Function
	BattleEngine(const BattleEngine& _Other) = delete;
	BattleEngine(BattleEngine&& _Other) noexcept = delete;
	BattleEngine& operator=(const BattleEngine& _Other) = delete;
	BattleEngine& operator=(BattleEngine&& _Other) noexcept = delete;
public:
	static inline BattleEngine* GetInst()
	{
		return Inst_;
	}

	static inline void Destroy()
	{
		if (Inst_ != nullptr)
		{
			delete Inst_;
			Inst_ = nullptr;
		}

	}
};