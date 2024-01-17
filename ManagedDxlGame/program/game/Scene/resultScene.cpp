#include "resultScene.h"
#include "../dxlib_ext/dxlib_ext.h"
#include"tittleScene.h"

ResultScene::ResultScene()
{
}

void ResultScene::Update(float delta_time)
{
	sequence_.update(delta_time);
}

void ResultScene::Draw()
{
	DrawStringEx(10, 10, -1, "ƒŠƒUƒ‹ƒg‰æ–Ê");
}

bool ResultScene::seqIdle(float delta_time)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		auto mgr = SceneManager::GetInstance();
		mgr->changeScene(new (TittleScene));
	}
	return true;
}
