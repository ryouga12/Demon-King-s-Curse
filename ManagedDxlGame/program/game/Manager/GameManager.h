//
//まとめるクラス
//


#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<unordered_map>
#include<string>
#include<vector>


class GameManager {
public:
	GameManager();
	~GameManager();

	void Update();
	void Draw();

	//何回も同じ画像をロードしない為の関数
	int LoadGraphEX(std::string gh);


//------------------------------------------------------------------------------------------------------------------------
// あたり判定
// 矩形と矩形の衝突検知 & 座標補正
	int IsIntersectRectToCorrectPosition(tnl::Vector3& a_now, const tnl::Vector3& a_prev, const int a_rect_size_w, const int a_rect_size_h,
		const tnl::Vector3& b, const int b_rect_size_w, const int b_rect_size_h) {

		const int NO_HIT = 0;
		const int CORRECT_LEFT = 1;
		const int CORRECT_RIGHT = 2;
		const int CORRECT_UP = 3;
		const int CORRECT_DOWN = 4;

		if (!tnl::IsIntersectRect(a_now, a_rect_size_w, a_rect_size_h, b, b_rect_size_w, b_rect_size_h)) return NO_HIT;

		tnl::Vector3 a_near = tnl::GetNearestRectPoint(a_prev, (float)a_rect_size_w, (float)a_rect_size_h, b);
		int n = GetRegionPointAndRect(a_near, b, b_rect_size_w, b_rect_size_h);

		if (0 == n) {
			float y = (a_now - a_prev).y;
			// 下向きに移動している場合は上に補正
			if (y >= 0) {
				a_now.y = b.y - (b_rect_size_h / 2) - (a_rect_size_h / 2);
				return CORRECT_UP;
			}
			// 上向きに移動している場合は左右どちらかに補正
			else {
				// 右に補正
				if (a_now.x > b.x) {
					a_now.x = b.x + (b_rect_size_w / 2) + (a_rect_size_w / 2);
					return CORRECT_RIGHT;
				}
				// 左に補正
				else {
					a_now.x = b.x - (b_rect_size_w / 2) - (a_rect_size_w / 2);
					return CORRECT_LEFT;
				}
			}
		}
		else if (2 == n) {
			float y = (a_now - a_prev).y;
			// 上向きに移動している場合は下に補正
			if (y <= 0) {
				a_now.y = b.y + (b_rect_size_h / 2) + (a_rect_size_h / 2);
				return CORRECT_DOWN;
			}
			// 上向きに移動している場合は左右どちらかに補正
			else {
				// 右に補正
				if (a_now.x > b.x) {
					a_now.x = b.x + (b_rect_size_w / 2) + (a_rect_size_w / 2);
					return CORRECT_RIGHT;
				}
				// 左に補正
				else {
					a_now.x = b.x - (b_rect_size_w / 2) - (a_rect_size_w / 2);
					return CORRECT_LEFT;
				}
			}
		}
		else if (1 == n) {
			float x = (a_now - a_prev).x;
			// 左向きに移動している場合は右に補正
			if (x <= 0) {
				a_now.x = b.x + (b_rect_size_w / 2) + (a_rect_size_w / 2);
				return CORRECT_RIGHT;
			}
			// 右向きに移動している場合は上下どちらかに補正
			else {
				// 上に補正
				if (a_now.y < b.y) {
					a_now.y = b.y - (b_rect_size_h / 2) - (a_rect_size_h / 2);
					return CORRECT_UP;
				}
				// 下に補正
				else {
					a_now.y = b.y + (b_rect_size_h / 2) + (a_rect_size_h / 2);
					return CORRECT_DOWN;
				}
			}
		}
		else if (3 == n) {
			float x = (a_now - a_prev).x;
			// 右向きに移動している場合は左に補正
			if (x >= 0) {
				a_now.x = b.x - (b_rect_size_w / 2) - (a_rect_size_w / 2);
				return CORRECT_LEFT;
			}
			// 左向きに移動している場合は上下どちらかに補正
			else {
				// 上に補正
				if (a_now.y < b.y) {
					a_now.y = b.y - (b_rect_size_h / 2) - (a_rect_size_h / 2);
					return CORRECT_UP;
				}
				// 下に補正
				else {
					a_now.y = b.y + (b_rect_size_h / 2) + (a_rect_size_h / 2);
					return CORRECT_DOWN;
				}
			}
		}
		return NO_HIT;
	}

private:


	int GetRegionPointAndRect(const tnl::Vector3& p, const tnl::Vector3& rp, const int rect_w, const int rect_h) {
		tnl::Vector3 v1 = tnl::Vector3::Normalize({ float(rect_h), float(rect_w), 0 });
		tnl::Vector3 v2 = tnl::Vector3::Normalize({ float(rect_h), float(-rect_w), 0 });
		//		tnl::Vector3 vc1 = v1.cross(tnl::Vector3(0, 0, 1));
		//		tnl::Vector3 vc2 = v2.cross(tnl::Vector3(0, 0, 1));
		tnl::Vector3 vc1 = v1;
		tnl::Vector3 vc2 = v2;

		int s1 = tnl::GetSidesPointAndPlane(p, vc1, rp);
		int s2 = tnl::GetSidesPointAndPlane(p, vc2, rp);
		if (s1 >= 0 && s2 >= 0) {
			return 1;
		}
		else if (s1 >= 0 && s2 <= 0) {
			return 2;
		}
		else if (s1 <= 0 && s2 >= 0) {
			return 0;
		}
		else {
			return 3;
		}
	}

//------------------------------------------------------------------------------------------------------------------------	
//一度読み込んだghを保存するmap
	std::unordered_map<std::string, int> ghmap;



};