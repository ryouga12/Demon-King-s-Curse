#pragma once
//�V�[���̊��N���X
#include "../Item/Inventory.h"



class BaseScene {
public:
    virtual void Update(float delta_time) {};
    virtual void Draw() = 0;
   

//------------------------------------------------------------------------------------------------------------------------
//���̃V�[���Ȃǂł��g�����ߋ��ʃ��\�b�h�ɂ���
   Shared<Inventory>inventory = nullptr;

   // ���ʏ�����C���x���g���̍X�V
   void UpdateCommon(float delta_time) {
       inventory->Update(delta_time);
   }
   void DrawCommon() {
       inventory->draw();
   }
   void SetInventory(Shared<Inventory>inventory_) {
       inventory = inventory_;
   }

};


