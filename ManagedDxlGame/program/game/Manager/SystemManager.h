#pragma once
///
///システム面を扱うマネージャー
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
//---武器関連---//



//------------------------------------------------------------------------------------------------------------------------
//---アイテム関連---//

	int GetRandEx(int a, int b);

private:

//------------------------------------------------------------------------------------------------------------------------
//---ポインタ---//

	Shared<Weapon>weapon_ = nullptr;
	Shared<Player>myPlayer = nullptr;
	MenuWindow::MenuElement_t* use_usable = nullptr;
	Shared<Item>item_ = nullptr;
	Shared<Inventory>inventory = nullptr;



	
};


