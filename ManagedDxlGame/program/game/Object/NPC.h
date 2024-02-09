#pragma once
///
///NPCクラス
///

enum  {
	NPC_DIR_DOWN,
	NPC_DIR_UP,
	NPC_DIR_LEFT,
	NPC_DIR_RIGHT,
	NPC_DIR_MAX
};


#include "../dxlib_ext/dxlib_ext.h"
#include"../Manager/Camera.h"

class Npc {
public:

	
	//Npcのコンストラクタ : 引数 : ( 名前 , 座標 , ハンドルのPass , 画像の大きさ , どのアニメーションから始めるか, ハンドルの数 )
	Npc(const std::string& name, const tnl::Vector3& pos , std::string ghdl_pass[], float scale , int animation_namber , int ghdl_num);
	void ChengeAnimation();

	void Update(float delta_time);
	void Draw(const Camera_& camera);

	std::string npc_name_;							//npcの名前
	int  npc_ghdl;									//npcの画像
	tnl::Vector3 npc_pos_ = {};					    //npcの座標
	int NpcCharaChipWidth  = 48;					//Npcのキャラチップの幅
	int NpcCharaChipHeight = 48;					//Npcのキャラチップの高さ


//------------------------------------------------------------------------------------------------------------------------
//アニメーション


	int animation_select = 0;						//Npcのアニメーションを切り替える
	
private:

	float scale_ = 0;								//それぞれの画像で使う大きさを決める
	float anim_time_count = 0;						//アニメーションのカウント
	int anim_ctrl_dir = NPC_DIR_DOWN;				//アニメーションの選択
	int anim_ctrl_frame = 0;						//フレーム
	int anim_hdls[NPC_DIR_MAX][5];					//アニメーションの配列


};