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


//‰æ‘œ‚ğd•¡‚µ‚Ä“Ç‚İ‚Ü‚È‚¢‚æ‚¤‚É‚±‚ê‚ğg‚¤
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
