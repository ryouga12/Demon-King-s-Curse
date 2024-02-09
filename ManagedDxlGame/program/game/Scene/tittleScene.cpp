#include "tittleScene.h"



TittleScene::TittleScene()
{
	gManager = new GameManager();

	tittle_Menu = std::make_shared<Menu>(525, 500, 250, 80, "graphics/WindowBase_02.png");

	tittle_ghdl = gManager->LoadGraphEX("graphics/tittle_background.png");

	enter_gh = gManager->LoadGraphEX("graphics/button_Enter.png");
	 

}

TittleScene::~TittleScene()
{
	delete gManager;
}

void TittleScene::Update(float delta_time)
{
	sequence_.update(delta_time);

	
}

void TittleScene::Draw()
{
	//�w�i�`��
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, tittle_ghdl, TRUE);

	//�^�C�g�����j���[�̕`��
	tittle_Menu->Menu_draw();


	DrawStringEx(10, 10, -1, "�^�C�g�����");

	//�^�C�g�����j���[�̗v�f
	DrawRotaGraph(tittle_Menu->menu_x + 125, tittle_Menu->menu_y + 25, 1, 0, enter_gh, true);
	DrawStringEx(tittle_Menu->menu_x + 10, tittle_Menu->menu_y + 50, String_Color_Black, "Enter�������ăQ�[���X�^�[�g");

	


}

bool TittleScene::seqIdle(float delta_time)
{


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		auto mgr = SceneManager::GetInstance();
		mgr->changeScene(new VillageScene());
	}
	return true;
}
