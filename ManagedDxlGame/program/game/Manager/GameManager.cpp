#include "GameManager.h"
#include "../dxlib_ext/dxlib_ext.h"

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::Update()
{
	
}

void GameManager::Draw()
{

	
}


//�摜���d�����ēǂݍ��܂Ȃ��悤�ɂ�����g��
int GameManager::LoadGraphEX(std::string gh)
{

	auto it = ghmap.find(gh);
	if (it != ghmap.end()) {
		return ghmap[gh];
	}

	else {
		int loadgh = LoadGraph(gh.c_str());
		ghmap.insert(std::make_pair(gh, loadgh));
	}


	return ghmap[gh];
}
