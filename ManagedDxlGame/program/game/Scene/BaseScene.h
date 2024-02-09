#pragma once
//シーンの基底クラス
#include "../Item/Inventory.h"



class BaseScene {
public:
    virtual void Update(float delta_time) {};
    virtual void Draw() = 0;
   

//------------------------------------------------------------------------------------------------------------------------
//他のシーンなどでも使うため共通メソッドにする
   Shared<Inventory>inventory = nullptr;

   // 共通処理やインベントリの更新
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


