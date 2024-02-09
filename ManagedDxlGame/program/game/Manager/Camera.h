//
//ƒJƒƒ‰ƒNƒ‰ƒX
//


#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Camera_ {
public:
	Camera_();
	

	void update(tnl::Vector3 target_pos, int MAP_WIDTH, int MAP_HEIGHT);
	void draw();

	tnl::Vector3 target_ = { 0, 0, 0 };
private:

	
};

