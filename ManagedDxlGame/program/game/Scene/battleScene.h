#pragma once
#include"../Scene/BaseScene.h"
#include "../dxlib_ext/dxlib_ext.h"


class BattleScene : public  BaseScene{
public:
	BattleScene();

	void Update(float delta_time)override;
	void Draw()override;


private:
	tnl::Sequence<BattleScene> sequence_ = tnl::Sequence<BattleScene>(this, &BattleScene::seqIdle);
	bool seqIdle(float delta_time);

	


};