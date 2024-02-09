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

class Player : public Actor {
public:

	
	Player();

	void Update(float delta_time);


	//---プレイヤー関係---//
	tnl::Vector3 plyer_pos = {};
	float first_pos_x = 195;						//ゲームが始まった時のｘ座標
	float first_pos_y = 312;						//ゲームが始まった時のy座標
	int Total_Frame = 3;							//プレイヤーの総フレーム(3)
	int Horizontal_frame = 3;						//プレイヤーの横フレーム(3)
	int Vertical_frame = 1;							//プレイヤーの縦フレーム(1)
	int Horizontal_oneframe = 32;					//横方向へ 1フレームあたりの幅(32)
	int Vertical_oneframe = 32;						//縦方向へ 1フレームあたりの幅(32)

	//plyerの歩数
	float numberStep = 0;
	//plyerの動きの制御
	bool plyControl = true;

	//playerの移動前座標
	tnl::Vector3 prev_pos = { 0 ,0,0 };


	const int CHARA_HEIGHT = 48;					//プレイヤーの高さ
	const int CHARA_WIDTH = 48;						//プレイヤーの幅

	//プレイヤーのお金
	int money = 0;

	//プレイヤーの最大HP
	int MaxHp = 0;

	//プレイヤーの動き
	void player_Move(float delta_time , const float& velocity);
	//プレイヤーの描画
	void player_draw(const Camera_& camera, float scale);
	
	tnl::Vector3 SetAndGetPlayerPosition(const tnl::Vector3& new_pos) {
		plyer_pos = new_pos;
		return plyer_pos;
	}

	//プレイヤーのステータスをロードする
	void PlyStatusLoad();

	//プレイヤーのMaxHpの更新処理
	int PlyerMaxHp(int id);

	//plyerのステータス
	typedef struct {
		int id;
		int hp;
		int Attack;
		int Defance;
		int Speed;
		int R_expoint;
		int level;
	}PlyerStatus;

	//セーブする時に使う配列
	std::vector<PlyerStatus>plyerstatusSave;
	

private:
	

	//アニメーションに使う変数
	float anim_time_count = 0;
	int anim_ctrl_dir = DIR_DOWN;
	int anim_ctrl_frame = 0;
	int anim_hdls[DIR_MAX][5];

	//plyerのステータスを管理する


	//Statusを入れる変数
	PlyerStatus plyer_Status;

	//構造体の総数
	int Ply_Status_Total_num;

	//構造体を格納する配列
	std::list<PlyerStatus>Ply_Status_Type;

	//csv読み取り用の配列
	std::vector<std::vector<tnl::CsvCell>>PlyerStatus_Csv_Info;

	//ステータスを管理するためのID
	int PlyerId = 1;

public:

	//プレイヤーのステータスを他のクラスなどで取得する
	PlyerStatus GetPlyerStatus(int id) const {
		auto it = std::find_if(Ply_Status_Type.begin(), Ply_Status_Type.end(), [id]
		(const PlyerStatus& status) {return status.id == id; });

		if (it != Ply_Status_Type.end()) {
			return *it;
		}
		else {
			// IDに対応するアイテムが見つからない場合は、適当なデフォルト値を返すかエラー処理を行うなど
			return PlyerStatus{};
		}

	}

	int GetPlayerId() {
		return PlyerId;
	}

	void PlyerSave();
	void PlyerLoad();


};

