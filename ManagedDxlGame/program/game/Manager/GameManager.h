//
//�܂Ƃ߂�N���X
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


	//��x�ǂݍ���gh��ۑ�����map
	std::unordered_map<std::string, int> ghmap;

};