#include "SystemManager.h"



SystemManager::SystemManager()
{
	weapon_ = std::make_shared<Weapon>();
	myPlayer = std::make_shared<Player>();
	item_ = std::make_shared<Item>();
	inventory = std::make_shared<Inventory>();


	/*menu_ = std::make_shared<MenuWindow>();*/

}

SystemManager::~SystemManager()
{
	
}

void SystemManager::draw()
{
	
}



int SystemManager::GetRandEx(int a, int b)
{

	if (a > b) {
		int diff = static_cast<int>(a - b);
		int random = static_cast<int>(GetRand(diff) + b);

		return random;
	}
	else {
		int diff = static_cast<int>(b - a);
		int random = static_cast<int>(GetRand(diff) + a);

		return random;
	}


	return 0;
}




