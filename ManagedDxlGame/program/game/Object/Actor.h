#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<string>

class Actor {
public:
	tnl::Vector3 pos = {};
	

protected:

	//���O
	std::string name = "";
	//����,�A�C�e���ɂ��ǉ��X�e�[�^�X
	int equipHp = 0;
	int equipAttack = 0;
	int equipDefance = 0;

	//��b�X�e�[�^�X
	int baseHp = 0;
	int baseAttack = 0;
	int baseDefance = 0;

	//�`��X�e�[�^�X
	int hp = 0;
	int attack = 0;
	int defance = 0;

	
};