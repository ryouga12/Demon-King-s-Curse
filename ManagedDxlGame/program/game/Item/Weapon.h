
///
///�����Ȃǂ̗v�f
/// 

#pragma once
#include "Item.h"
#include<unordered_map>
#include"../Object/Actor.h"
#include "../dxlib_ext/dxlib_ext.h"
#include"../Item/ItemBase.h"


class Weapon : public ItemBase{
public:

	Weapon();

	void draw();

	

	//������i�[����z��
	std::vector<ItemBase>weponList;

	//���퉮�Ŏg�����i�̐����ƍ��W
	std::string weapon_disc[6];

	//����̒l�𑼂̃N���X�Ŏg��
	std::vector<ItemBase> GetWeaponValue()
	{
		return weponList;
	}

	//���탊�X�g�̐����擾����
	int GetWeaponListCount(){
		return weponList.size();
	}

	//����̒l���Z�b�g����֐�
	void WeaponInint();
	
	
private:

	
//------------------------------------------------------------------------------------------------------------------------
//---�|�C���^---//

	Shared<Item>item_ = nullptr;



};