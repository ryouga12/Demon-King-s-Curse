#pragma once
#include"../Scene/BaseScene.h"
#include"../Manager/SceneManager.h"


class ResultScene : public BaseScene {
public :
	ResultScene();

	void Update(float delta_time)override;
	void Draw()override;
		
private:

	tnl::Sequence<ResultScene> sequence_ = tnl::Sequence<ResultScene>(this, &ResultScene::seqIdle);
	bool seqIdle(float delta_time);
};
