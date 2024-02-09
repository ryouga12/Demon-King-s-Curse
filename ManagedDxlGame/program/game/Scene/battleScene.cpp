#include "battleScene.h"
#include"../Manager/SceneManager.h"
#include"mapScene.h"
#include"resultScene.h"

BattleScene::BattleScene()
{

}

void BattleScene::Update(float delta_time)
{
	sequence_.update(delta_time);
}

void BattleScene::Draw()
{
	DrawStringEx(10, 10, -1, "ƒoƒgƒ‹‰æ–Ê");
}

bool BattleScene::seqIdle(float delta_time)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		auto mgr = SceneManager::GetInstance();
		mgr->changeScene(new ResultScene());
	}
	return true;
}
