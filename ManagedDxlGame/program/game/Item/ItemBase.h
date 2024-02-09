#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class ItemBase {
public:

	ItemBase();

	std::string name;
	int id = 0;
	int type = 0;
	int damage = 0;
	int epic = 0;
	int defance = 0;
	int price = 0;

	/*virtual void draw();*/


};