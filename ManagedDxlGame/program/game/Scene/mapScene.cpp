#include "mapScene.h"
#include"../Manager/SceneManager.h"
#include"resultScene.h"

MapScene::MapScene()
{

}

void MapScene::Update(float delta_time)
{
	sequence_.update(delta_time);
}

void MapScene::Draw()
{
	DrawStringEx(10, 10, -1, "ƒ}ƒbƒv‰æ–Ê");
}

bool MapScene::seqIdle(float delta_time)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		auto mgr = SceneManager::GetInstance();
		mgr->changeScene(new ResultScene());
	}
	return true;
}
