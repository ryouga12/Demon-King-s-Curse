#pragma once
///
///�V�X�e���ʂ������}�l�[�W���[
/// 

#include"../Item/Item.h"
#include"../Item/Weapon.h"
#include"../Item/Inventory.h"
#include"../Menu/MenuWindow.h"
#include"../Object/Player.h"
#include "../dxlib_ext/dxlib_ext.h"


class SystemManager {
public:
	SystemManager();
	~SystemManager();

	void draw();

	int selectNum;


//------------------------------------------------------------------------------------------------------------------------
//---����֘A---//



//------------------------------------------------------------------------------------------------------------------------
//---�A�C�e���֘A---//

	int GetRandEx(int a, int b);

private:

//------------------------------------------------------------------------------------------------------------------------
//---�|�C���^---//

	Shared<Weapon>weapon_ = nullptr;
	Shared<Player>myPlayer = nullptr;
	MenuWindow::MenuElement_t* use_usable = nullptr;
	Shared<Item>item_ = nullptr;
	Shared<Inventory>inventory = nullptr;



	
};


