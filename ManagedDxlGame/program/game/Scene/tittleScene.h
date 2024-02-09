#pragma once
///
///�^�C�g����ʂ̏����Ȃ�
///


#include"../Scene/BaseScene.h"
#include "../dxlib_ext/dxlib_ext.h"
#include"../Manager/SceneManager.h"
#include"village.h"
#include"../Manager/GameManager.h"
#include"../Menu/MenuWindow.h"
#include"../Item/Item.h"

class TittleScene : public BaseScene  {
public:

	TittleScene();
	~TittleScene();

	void Update(float delta_time) override;
	void Draw()override;

	


private:
	tnl::Sequence<TittleScene> sequence_ = tnl::Sequence<TittleScene>(this, &TittleScene::seqIdle);
	bool seqIdle(float delta_time);


	//�w�i�摜
	int tittle_ghdl = 0;

	//�J���[�i���j
	int String_Color_Black = 0;

	//enter�{�^��
	int enter_gh = 0;

	


//------------------------------------------------------------------------------------------------------------------------	
//�|�C���^

	GameManager* gManager = nullptr;
	Shared<Menu> tittle_Menu = nullptr;

	
	
};