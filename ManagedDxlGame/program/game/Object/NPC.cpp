#include "NPC.h"

Npc::Npc(const std::string& name, const tnl::Vector3& pos, std::string ghdl_pass[], float scale , int animation_namber , int ghdl_num)
{
	//引数を代入して呼び出し元で使う
	npc_name_ = name;
	npc_pos_ = pos;
	scale_ = scale;
	animation_select = animation_namber;
	
	for (int i = 0; i < ghdl_num; i++)
	{
		LoadDivGraph(ghdl_pass[i].c_str(), 3, 3, 1, 32, 32, anim_hdls[i]);
	}

}

//Npcのアニメーションを切り替える
void Npc::ChengeAnimation()
{
	switch (animation_select) {

	case NPC_DIR_DOWN:

		anim_ctrl_dir = NPC_DIR_DOWN;

		break;

	case NPC_DIR_UP:

		anim_ctrl_dir = NPC_DIR_UP;

		break;

	case NPC_DIR_LEFT:

		anim_ctrl_dir = NPC_DIR_LEFT;

		break;

	case NPC_DIR_RIGHT:

		anim_ctrl_dir = NPC_DIR_RIGHT;

		break;

	default:

		anim_ctrl_dir = NPC_DIR_DOWN;

		break;

	}
}

void Npc::Update(float delta_time)
{
	//アニメーション
	anim_time_count += delta_time;
	if (anim_time_count > 0.1f) {
		anim_ctrl_frame++;
		anim_ctrl_frame %= 3;

		anim_time_count = 0;
	}

}

void Npc::Draw(const Camera_& camera)
{
	tnl::Vector3 draw_pos = npc_pos_ - camera.target_ + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawRotaGraph(draw_pos.x, draw_pos.y, scale_, 0, anim_hdls[anim_ctrl_dir][anim_ctrl_frame], true);
}
