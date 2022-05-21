#pragma once

enum class PokemonType
{
	NORMAL, //노말
	FIRE, //불
	WATER, //물
	GRASS, // 풀
	ELECTRIC, //전기
	ICE, //얼음
	FIGHTING, //격투
	POISON, //독
	GROUND, //땅
	FLYING, //비행
	PSYCHIC, //에스퍼
	BUG, //벌레
	ROCK, //바위
	GHOST, //고스트
	DRAGON //드래곤
};

//상태 이상
enum class StatusEffect
{
	NONE,
	PSN, //맹독
	BRN, //화상
	PAR, //마비
	SLP, //잠듦
	FRZ, //얼음
};

//스킬 종류
enum class SkillType
{
	Physical,
	Special,
	Status
};


//아이템의 종류
enum class ItemType
{
	ITEM,
	KEYITEM,
	BALL
};