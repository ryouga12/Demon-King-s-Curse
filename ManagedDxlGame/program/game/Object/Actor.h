#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<string>

class Actor {
public:
	tnl::Vector3 pos = {};
	

protected:

	//名前
	std::string name = "";
	//装備,アイテムによる追加ステータス
	int equipHp = 0;
	int equipAttack = 0;
	int equipDefance = 0;

	//基礎ステータス
	int baseHp = 0;
	int baseAttack = 0;
	int baseDefance = 0;

	//描画ステータス
	int hp = 0;
	int attack = 0;
	int defance = 0;

	
};