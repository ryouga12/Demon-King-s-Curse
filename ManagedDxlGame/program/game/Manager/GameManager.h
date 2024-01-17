//
//まとめるクラス
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


	//一度読み込んだghを保存するmap
	std::unordered_map<std::string, int> ghmap;

};