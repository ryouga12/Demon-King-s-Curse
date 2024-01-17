//
//‚Ü‚Æ‚ß‚éƒNƒ‰ƒX
//


#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<unordered_map>
#include<string>
#include<vector>


class GameManager {
public:
	GameManager();
	~GameManager();

	void Update();
	void Draw();

	int LoadGraphEX(std::string gh);


	//ˆê“x“Ç‚İ‚ñ‚¾gh‚ğ•Û‘¶‚·‚émap
	std::unordered_map<std::string, int> ghmap;

};