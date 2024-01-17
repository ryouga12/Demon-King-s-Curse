#pragma once
///
///プレイヤーに関するクラス
/// 


#include "../dxlib_ext/dxlib_ext.h"
#include"Actor.h"
#include"../Manager/Camera.h"

class Actor;

enum {
	DIR_DOWN,
	DIR_UP,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_MAX
};

class Player : public Actor{
public:

	/*Player();*/
	Player( float Hp, int Attack, int Defence);

	tnl::Vector3 plyer_pos = {};
	float first_pos_x = 195;						//ゲームが始まった時のｘ座標
	float first_pos_y = 312;						//ゲームが始まった時のy座標
	int Total_Frame = 3;							//プレイヤーの総フレーム(3)
	int Horizontal_frame = 3;						//プレイヤーの横フレーム(3)
	int Vertical_frame = 1;							//プレイヤーの縦フレーム(1)
	int Horizontal_oneframe = 32;					//横方向へ 1フレームあたりの幅(64)
	int Vertical_oneframe = 32;						//縦方向へ 1フレームあたりの幅(64)



	const int CHARA_HEIGHT = 64;					//プレイヤーの高さ
	const int CHARA_WIDTH = 64;						//プレイヤーの幅

	void Update(float delta_time);

	//プレイヤーの動き
	void player_Move(float delta_time);
	//プレイヤーの描画
	void player_draw(const Camera_& camera);

private:
	

	//アニメーションに使う変数
	float anim_time_count = 0;
	int anim_ctrl_dir = DIR_DOWN;
	int anim_ctrl_frame = 0;
	int anim_hdls[DIR_MAX][5];

	//plyerの歩数
	float numberStep = 0;

};

