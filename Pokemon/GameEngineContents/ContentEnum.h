#pragma once

//포켓몬 타입
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

//포켓몬 상태 이상
enum class StatusEffect
{
	NONE,
	PSN, //맹독
	BRN, //화상
	PAR, //마비
	SLP, //잠듦
	FRZ, //얼음
};

//포켓몬 성격
enum class PokemonNature
{
	Quirky, //변덕
	Bold, //대담
	Modest, //조심
	Calm, //차분
	Timid, //겁쟁이
	Lonely, //외로운
	Bashful, //수줍음
	Mild, //의젓
	Gentle, //얌전
	Hasty, //성급
	Adamant, //고집스런
	Impish, //장난꾸러기
	Hardy, //노력
	Careful, //신중
	Jolly, //명랑
	Naughty, //개구쟁이
	Lax, //촐랑
	Rash, //덜렁
	Docile, //온순
	Naive, //천진난만
	Brave, //용감
	Relaxed, //무사태평
	Quiet, //냉정
	Sassy, //건방
	Serious, //성실
	End 
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


enum class RenderOrder
{
	Background,
	Player = 1,
	UI = 15
};
